import sys, logging
import asyncio

from bleak import BleakClient
from bleak import _logger as logger

# https://learn.adafruit.com/introducing-adafruit-ble-bluetooth-low-energy-friend/uart-service
UART_TX_UUID = "0x0002"
MAC_ADDRESS = "AA:AA:AA:AA:AA:AA"

async def uart_write(address, cmd):
    async with BleakClient(address) as client:
        logger.info(f"Connected: {client.is_connected}")

        write_value = cmd.encode("ascii")
        print(write_value)
        await client.write_gatt_char(UART_TX_UUID, write_value)

l = logging.getLogger("asyncio")
l.setLevel(logging.DEBUG)
h = logging.StreamHandler(sys.stdout)
h.setLevel(logging.DEBUG)
l.addHandler(h)
logger.addHandler(h)

loop = asyncio.get_event_loop()
loop.run_until_complete(uart_write(MAC_ADDRESS, sys.argv[1]))