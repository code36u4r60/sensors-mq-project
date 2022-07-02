#!/usr/local/bin/python3

# Simple way to query connected USB devices info in Python?
# https://newbedev.com/simple-way-to-query-connected-usb-devices-info-in-python

# usb.product
# uThingVOC         - uThingVOC
# ESP32             - CP2104 USB to UART Bridge Controller
# ARDUINO ELEGOO    - IOUSBHostDevice
# ARDUINO           - USB2.0-Serial
# ARDUINO Original  - Arduino Uno

# IMPORTS
import os
import re

from typing import Union, Tuple

import serial
import json
import csv
import yaml
from datetime import datetime
from json import JSONDecodeError
from serial import Serial
from signal import signal, SIGINT
import serial.tools.list_ports as list_ports
import pandas as pd

from air_quality import AirQuality


def __board_setup(port, baud=9600, timeout=1, set_config='') -> Serial:
    if not port:
        raise Exception('ERROR(board_setup): Indicate a communication port.')

    uart = serial.Serial(port, baud, timeout=timeout)

    if set_config:
        uart.write(set_config.encode())

    return uart


def board_setup(port_info) -> Union[Serial, Serial, Serial, Serial]:
    for c in config:
        if port_info.serial_number in c["devices"]:
            return __board_setup(port_info.device, c['baud'], c['timeout'], c['set-config'])


def u_thing_voc_read_values(uart) -> dict:
    uart.flushInput()
    while True:
        try:
            __json = uart.readline().decode()
            __data = dict(json.loads(__json))
            __data["IAQ Classification"] = iaq_classification(__data['IAQ']).value['air_quality']
            return __data
        except (JSONDecodeError, AttributeError):
            pass
        except Exception:
            raise Exception('ERROR(u_thing_voc_read_values).')


def esp32_voc_read_values(uart) -> dict:
    uart.flushInput()
    while True:
        try:
            __json = uart.readline().decode()
            __data = json.loads(__json)
            for __row in __data['sensors']:
                __row["IAQ Classification"] = iaq_classification(__row['iac']).value['air_quality']
            return __data
        except (JSONDecodeError, AttributeError):
            pass
        except Exception:
            raise Exception('ERROR(esp32_voc_read_values).')


def create_compact_excel_file() -> None:
    __csv_files = os.listdir(folder_path_csv)

    __writer = pd.ExcelWriter(os.path.join(
        folder_path_excel, 'resume.xlsx'), engine='xlsxwriter')

    for __file_name in __csv_files:
        __csv_data = pd.read_csv(os.path.join(folder_path_csv, __file_name),
                                 encoding="utf-8",
                                 low_memory=False)
        __name = re.split(r'\\|/|\.', __file_name)[-2]

        if len(__name) > 30:
            __words = __name.split()
            __name = __words[0] + __words[-1]

        __csv_data.to_excel(os.path.join(folder_path_excel,
                                         f"{__name}.xlsx"), encoding="utf-8")
        __csv_data.to_excel(__writer, sheet_name=__name, index=False)

    __writer.save()


def handler(event, context) -> None:
    program_header()
    res = input("\nCtrl-c was pressed. Do you really want to exit? y/n ").lower()
    if res == 'y':
        create_file = input(
            "Want to create a compact excel file? y/n ").lower()
        if create_file == 'y':
            program_header()
            print("In process...")
            create_compact_excel_file()
        exit(1)


def program_header() -> None:
    os.system('cls' if os.name == 'nt' else 'clear')
    print("\033[0;0H")
    print("." * 110)
    print("MIEEC - Sensor project\n")
    print("Ports in use....")
    for _device in devices:
        print(_device["description"], " : ", _device["serial_number"])
    print("." * 120)


def exists(device) -> bool:
    for __device in devices:
        if __device["serial_number"] == device.serial_number:
            return True
    return False


def update_devices(list_devices):
    if not devices:
        for __device in __list_devices:
            __uart = board_setup(__device)
            devices.append(
                {
                    "description": __device.description,
                    "serial_number": __device.serial_number,
                    "uart": __uart
                }
            )
    else:
        for __device in list_devices:
            if not exists(__device):
                __uart = board_setup(__device)
                devices.append(
                    {
                        "description": __device.description,
                        "serial_number": __device.serial_number,
                        "uart": __uart
                    }
                )

        if not len(devices) == len(list_devices):
            for __device in devices:
                exist = False
                for __dev in list_devices:
                    if __device["serial_number"] == __dev.serial_number:
                        exist = True
                        break
                if not exist:
                    devices.remove(__device)


def iaq_classification(iaq: int):
    if iaq < 0:
        return None
    if iaq <= 50:
        return AirQuality.green
    if iaq <= 100:
        return AirQuality.dark_green
    if iaq <= 150:
        return AirQuality.yellow
    if iaq <= 200:
        return AirQuality.orange
    if iaq <= 350:
        return AirQuality.purple
    return AirQuality.brown


def create_directory(__name) -> Tuple[str, str]:
    __folders = list(filter(lambda x: os.path.isdir(x), os.listdir(path_root)))
    __folder_path = os.path.join(path_root, "data_files")

    if "data_files" not in __folders:
        os.mkdir(__folder_path)

    __name = "default" if __name == "-d" or __name == "default" else f"{__name}_{str(datetime.now().date())}"

    __folders = os.listdir(__folder_path)
    __folder_path = os.path.join(__folder_path, __name)

    if __name not in __folders:
        os.mkdir(__folder_path)

    __folder_path_csv = os.path.join(__folder_path, "csv")
    __folder_path_excel = os.path.join(__folder_path, "excel")

    __folders = os.listdir(__folder_path)

    if "csv" not in __folders:
        os.mkdir(__folder_path_csv)

    if "excel" not in __folders:
        os.mkdir(__folder_path_excel)

    return __folder_path_csv, __folder_path_excel


def read_values(__devices) -> list:
    __data = []

    for __device in __devices:

        for __c in config:
            if __device['serial_number'] in __c["devices"]:
                __name = __c["name"].strip()
                break

        if __name and __name == "uThingVOC":
            __resp = u_thing_voc_read_values(__device["uart"])

        elif __name and __name == "CP2104 USB to UART Bridge Controller":
            __resp = esp32_voc_read_values(__device["uart"])
            __resp = list(__resp['sensors'])

        __data.append({
            "name": __name,
            "serial_number": __device['serial_number'],
            "data": __resp
        })

    return __data


def show_values(__data: list) -> None:
    program_header()
    print("Time: ", str(datetime.now()), "\n")

    for d in __data:
        print(f"{d['name']} - {d['serial_number']}")

        if isinstance(d['data'], dict):
            for key in d['data'].keys():
                print("{:^15s}".format(key), end='')
            print('')

            for value in d['data'].values():
                print("{:^15}".format(value), end='')
            print()

        if isinstance(d['data'], list):
            for key in d['data'][0].keys():
                print("{:^15s}".format(key), end='')
            print('')

            for row in d['data']:
                for value in row.values():
                    print("{:^15}".format(value), end='')
                print()
        print()


def save_in_csv(__data, __folder_path_csv) -> None:
    __files = os.listdir(__folder_path_csv)

    for __d in data:
        __sensor_name = get_name(__d)
        __name = "{}_{}.csv".format(__sensor_name, __d['serial_number'])

        if len(__name) > 30:
            __words = __name.split()
            __name = __words[0] + __words[-1]

        __path = os.path.join(__folder_path_csv, __name)

        if __name not in __files:
            with open(__path, 'w', encoding='UTF8', newline='\n') as f:
                writer = csv.writer(f)
                writer.writerow(["time", *__d["keys"]])

        with open(__path, 'a', encoding='UTF8', newline='\n') as f:
            writer = csv.writer(f)
            if __sensor_name in "uThingVOC":
                writer.writerow([str(datetime.now()), *__d["values"]])

            elif __sensor_name in "CP2104 USB to UART Bridge Controller":
                for row in __d["values"]:
                    writer.writerow([str(datetime.now()), *row])


def info_devices(__list_devices):
    for __device in __list_devices:
        print("Device: ", __device.device)
        print("Name: ", __device.name)
        print("Description: ", __device.description)
        print("HWID: ", __device.hwid)
        print("VID: ", __device.vid)
        print("PID: ", __device.pid)
        print("Serial_number: ", __device.serial_number)
        print("Location: ", __device.location)
        print("Manufacturer: ", __device.manufacturer)
        print("Product: ", __device.product)
        print("Interface: ", __device.interface)
    input('Press "enter" to continue...')


def get_name(device):
    __name = ''
    for __c in config:
        if device['serial_number'] in __c["devices"]:
            __name = __c["name"].strip()
            break
    return __name


if __name__ == '__main__':

    # This function is used to prevent "ctrl-c" or other forced interruption
    signal(SIGINT, handler)

    # Variables
    devices = list()  # all important devices

    # Save the path to the root directory
    path_root = os.path.abspath(os.getcwd())

    # Read all configurations from config.yamlconfig.yaml
    # If config.yaml does not exist, create a "config.yaml"
    # file in the root directory. Use the "__reference__config.yaml"
    # to help you
    with open('config.yaml', 'r') as f:
        __yaml = yaml.load(f, Loader=yaml.FullLoader)
        config = __yaml['config']

        while True:
            try:
                # Create a folder to save the tests session
                name = input('What is the name you want to give this test session?\n Write ("default" or "-d") to '
                             'save in default file. #> ').lower()

                if not name:
                    program_header()
                    print(
                        "\n🚨 I have a little problem to understand your choice.\nSorry 😞, write again... \n")
                else:
                    break
            except Exception as e:
                print(e)
                exit(1)

    # crate directory to save data
    folder_path_csv, folder_path_excel = create_directory(name)
    data = list()

    while True:
        # List all devices connected to a serial port
        __list_devices = list_ports.comports()
        # info_devices(__list_devices)

        # Filter all pre-referenced devices (config.yaml)
        serial_number = []
        for __conf in config:
            serial_number += __conf["devices"]

        __list_devices = list(filter(lambda __device: __device.serial_number in serial_number, __list_devices))
        # info_devices(__list_devices)

        # Update device list and configure devices
        update_devices(__list_devices)

        # Read values from all sensors
        data = read_values(devices)

        # Show read values
        show_values(data)

        # Save information in csv file
        # if data:
        # save_in_csv(data, folder_path_csv)
