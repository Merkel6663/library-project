import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import pytest
from smarthome import SmartHouse, Light, Thermostat, Camera, TV, User

@pytest.fixture
def home():
    return SmartHouse()

@pytest.fixture
def admin():
    return User("admin", "ADMIN")

@pytest.fixture
def resident():
    return User("resident", "RESIDENT")

@pytest.fixture
def guest():
    return User("guest", "GUEST")

@pytest.fixture
def lamp():
    return Light("L1", "Lamp in living room")

@pytest.fixture
def thermostat():
    return Thermostat("T1", "Thermostat in living room")

@pytest.fixture
def camera():
    return Camera("C1", "Camera in living room")

@pytest.fixture
def tv():
    return TV("TV1", "TV in living room")