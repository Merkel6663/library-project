import pytest

def test_admin_permission(admin, lamp, camera, tv, thermostat, home):
    home.add_device(lamp)
    home.add_device(camera)
    home.add_device(tv)
    home.add_device(thermostat)

    home.control_device(admin, "L1", "turn_on")
    lamp = home.find_device("L1")
    assert "ON" in lamp.get_status()
    
    home.control_device(admin, "L1", "set_brightness", value=75)
    assert lamp.brightness == 75
    
    home.control_device(admin, "T1", "turn_on")
    thermo = home.find_device("T1")
    assert "ON" in thermo.get_status()
    
    home.control_device(admin, "T1", "set_temperature", value=22.5)
    thermo = home.find_device("T1")
    assert thermo.target_temperature == 22.5
    
    home.control_device(admin, "C1", "turn_on")
    camera = home.find_device("C1")
    assert "ON" in camera.get_status()
    
    home.control_device(admin, "C1", "start_recording")
    assert "recording is ON" in camera.get_status()


def test_resident_can_control_lights_and_thermostat(resident, lamp, camera, tv, thermostat, home):

    home.add_device(lamp)
    home.add_device(camera)
    home.add_device(tv)
    home.add_device(thermostat)
    
    home.control_device(resident, "L1", "turn_on")
    lamp = home.find_device("L1")
    status = lamp.get_status()
    assert "ON" in status
    
    home.control_device(resident, "L1", "set_brightness", value=50)
    assert lamp.brightness == 50
    
    home.control_device(resident, "T1", "turn_on")
    thermo = home.find_device("T1")
    status = thermo.get_status()
    assert "ON" in status
    
    home.control_device(resident, "T1", "set_temperature", value=21.0)
    assert thermo.target_temperature == 21.0
    
    with pytest.raises(PermissionError):
        home.control_device(resident, "C1", "turn_on")
    
    with pytest.raises(PermissionError):
        home.control_device(resident, "C1", "start_recording")


def test_guest_can_only_toggle_lights(guest, lamp, camera, tv, thermostat, home):
    
    home.add_device(lamp)
    home.add_device(camera)
    home.add_device(tv)
    home.add_device(thermostat)

    home.control_device(guest, "L1", "turn_on")
    lamp = home.find_device("L1")
    status = lamp.get_status()
    assert "ON" in status
    
    home.control_device(guest, "L1", "turn_off")
    status = lamp.get_status()
    assert "OFF" in status
    
    with pytest.raises(PermissionError):
        home.control_device(guest, "L1", "set_brightness", value=80)
    
    with pytest.raises(PermissionError):
        home.control_device(guest, "T1", "turn_on")
    
    with pytest.raises(PermissionError):
        home.control_device(guest, "T1", "set_temperature", value=25)
    
    with pytest.raises(PermissionError):
        home.control_device(guest, "C1", "turn_on")