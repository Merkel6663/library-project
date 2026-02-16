import pytest

def test_camera_default_stat(camera):
    status = camera.get_status()
    assert "Camera is OFF" in status
    assert "recording is OFF" in status

def test_camera_turn_on(camera):
    camera.turn_on()
    status = camera.get_status()
    assert "Camera is ON" in status

def test_camera_turn_off(camera):
    camera.turn_off()
    status = camera.get_status()
    assert "Camera is OFF" in status

def test_camera_rec_on(camera):
    camera.turn_on()
    camera.start_recording()
    status = camera.get_status()
    assert "recording is ON" in status

def test_camera_rec_off(camera):
    camera.turn_on()
    camera.start_recording()
    camera.stop_recording()
    status = camera.get_status()
    assert "recording is OFF" in status

def test_camera_multiple_rec_on(camera):
    camera.turn_on()
    camera.start_recording()
    camera.start_recording()
    status = camera.get_status()
    assert "recording is ON" in status