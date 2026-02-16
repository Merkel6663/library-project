import pytest

def test_tv_turn_on_off(tv):
    tv.turn_on()
    status = tv.get_status()
    assert "TV is ON" in status

    tv.turn_off()
    status = tv.get_status()
    assert "TV is OFF" in status

def test_tv_change_channel(tv):
    tv.turn_on()
    tv.change_channel(15)
    assert tv.current_channel == 15

@pytest.mark.parametrize("invalid_channels", [-10, 50])
def test_tv_invalid_channels(invalid_channels, tv):
    tv.turn_on()
    with pytest.raises(Exception):
        tv.change_channel(invalid_channels)

def test_change_channel_while_off(tv):
    tv.turn_off()
    with pytest.raises(Exception):
        tv.change_channel(30)

def test_tv_set_volume(tv):
    tv.turn_on()
    tv.set_volume(45)
    assert tv.volume == 45

@pytest.mark.parametrize("invalid_volume", [-10, 110])
def test_tv_invalid_volume(invalid_volume, tv):
    tv.turn_on()
    with pytest.raises(Exception):
        tv.set_volume(invalid_volume)

def test_set_volume_while_off(tv):
    tv.turn_off()
    with pytest.raises(Exception):
        tv.set_volume(30)
