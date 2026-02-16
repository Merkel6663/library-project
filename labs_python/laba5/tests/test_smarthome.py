import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import pytest
from smarthome import Light

def test_add_new_device(home, lamp):
    home.add_device(lamp)
    assert "L1" in home._devices
    assert home._devices["L1"] == lamp

def test_same_index_err(home, lamp):
    home.add_device(lamp)
    new_lamp = Light("L1", "Lamp in bedroom")
    with pytest.raises(Exception):
        home.add_device(new_lamp)
    
def test_rem_device(home, lamp):
    home.add_device(lamp)
    assert "L1" in home._devices
    home.remove_device("L1")
    assert "L1" not in home._devices

def test_rem_nonexist_device(home):
    with pytest.raises(Exception):
        home.remove_device("NON_EXIST_DEVICE")

def test_find_device(home, lamp):
    home.add_device(lamp)
    assert home.find_device("L1") == lamp

