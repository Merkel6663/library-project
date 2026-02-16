import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import pytest
from smarthome import Device, Light, Thermostat, Camera

def test_device_init(lamp, camera, thermostat, tv):

    assert lamp.device_id == "L1"
    assert lamp._name == "Lamp in living room"

    assert camera.device_id == "C1"
    assert camera._name == "Camera in living room"

    assert thermostat.device_id == "T1"
    assert thermostat._name == "Thermostat in living room"

    assert tv.device_id == "TV1"
    assert tv._name == "TV in living room"

def test_device_turn_on_off(lamp, camera, thermostat, tv):
    lamp.turn_on()
    status = lamp.get_status()
    assert "Light is ON" in status
    lamp.turn_off()
    status = lamp.get_status()
    assert "Light is OFF" in status

    camera.turn_on()
    status = camera.get_status()
    assert "Camera is ON" in status
    camera.turn_off()
    status = camera.get_status()
    assert "Camera is OFF" in status

    thermostat.turn_on()
    status = thermostat.get_status()
    assert "Thermostat is ON" in status
    thermostat.turn_off()
    status = thermostat.get_status()
    assert "Thermostat is OFF" in status

    tv.turn_on()
    status = tv.get_status()
    assert "TV is ON" in status
    tv.turn_off()
    status = tv.get_status()
    assert "TV is OFF" in status

def test_device_cannot_be_created_with_empty_id():
    
    with pytest.raises(ValueError):
        Light("", "Лампа без ID")
    
    with pytest.raises(ValueError):
        Thermostat("", "Термостат без ID")
    
    with pytest.raises(ValueError):
        Camera("", "Камера без ID")


def test_device_cannot_be_created_with_empty_name():
    
    with pytest.raises(ValueError):
        Light("L1", "")
    
    with pytest.raises(ValueError):
        Thermostat("T1", "")
    
    with pytest.raises(ValueError):
        Camera("C1", "")