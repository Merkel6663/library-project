import pytest

def test_cur_temp(thermostat):
    with pytest.raises(AttributeError):
        thermostat.current_temperature = 30

def test_target_temp_change(thermostat):
    thermostat.set_temperature(30)
    assert thermostat.target_temperature == 30

@pytest.mark.parametrize("invalid_tar_temp", [-60, 60, 51, -51])
def test_target_temp_lim(thermostat, invalid_tar_temp):
    with pytest.raises(ValueError):
        thermostat.set_temperature(invalid_tar_temp)

def test_status_change(thermostat):
    prev_status = thermostat.get_status
    thermostat.set_temperature(-10)
    status = thermostat.get_status()
    assert prev_status != status
