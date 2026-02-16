import pytest

def test_default_status(lamp):
    status = lamp.get_status()
    assert "Light is OFF" in status

def test_turn_on(lamp):
    lamp.turn_on()
    status = lamp.get_status()
    assert "Light is ON" in status

def test_brightness_change(lamp):
    lamp.set_brightness(70)
    assert lamp.brightness == 70

@pytest.mark.parametrize("invalid_brightness", [-10, 200])
def test_invalid_brightness_value(lamp, invalid_brightness):
    with pytest.raises(ValueError):
        lamp.set_brightness(invalid_brightness)

def test_save_brightness(lamp):
    lamp.turn_on()
    lamp.set_brightness(30)
    lamp.turn_off()
    assert lamp.brightness == 30