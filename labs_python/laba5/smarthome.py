from abc import ABC, abstractmethod

class Device(ABC):
    def __init__(self, id, name):
        self._id = id
        self._name = name

    @abstractmethod
    def turn_on(self):
        pass

    @abstractmethod
    def turn_off(self):
        pass

    @abstractmethod
    def get_status(self):
        pass


    @property
    def device_id(self):
        return self._id
    
    def execute_command(self, command, **kwargs):
        if hasattr(self, command):
            method = getattr(self, command)
            return method(**kwargs)
        else:
            return f'Неизвестная команда: {command}'

class Light(Device):
    def __init__(self, id, name):
        if not id or not name:
            raise ValueError("ID и имя обязательны")
        super().__init__(id, name)
        self._is_on = False
        self._brightness = 0

    @property
    def brightness(self):
        return self._brightness
    
    @brightness.setter
    def brightness(self, value):
        if 0 <= value <= 100:
            self._brightness = value
        else:
            raise ValueError('Brightness must be between 0 and 100')
    
    def turn_on(self):
        self._is_on = True

    def turn_off(self):
        self._is_on = False
    
    def get_status(self):
        return f"Light is {'ON' if self._is_on else 'OFF'}, brightness {self._brightness}"
    
    def set_brightness(self, value):
        self.brightness = value
    
class Thermostat(Device):
    def __init__(self, id, name):
        if not id or not name:
            raise ValueError("ID и имя обязательны")
        super().__init__(id, name)
        self._cur_temp = 0
        self._target_temp = 0
        self._is_on = False

    @property
    def current_temperature(self):
        return self._cur_temp
    
    @property
    def target_temperature(self):
        return self._target_temp
    
    @target_temperature.setter
    def target_temperature(self, value):
        if -50 <= value <= 50:
            self._target_temp = value
        else:
            raise ValueError("Target temperature must be between -50 and 50")

    def turn_on(self):
        self._is_on = True

    def turn_off(self):
        self._is_on = False

    def get_status(self):
        return f"Thermostat is {'ON' if self._is_on else 'OFF'}, current temp {self._cur_temp}, target temp {self._target_temp}"
    
    def set_temperature(self, value):
        self.target_temperature = value
    
class Camera(Device):
    def __init__(self, id, name):
        if not id or not name:
            raise ValueError("ID и имя обязательны")
        super().__init__(id, name)
        self._is_on = False
        self._is_recording = False

    def turn_on(self):
        self._is_on = True

    def turn_off(self):
        self._is_on = False
        self._is_recording = False

    def start_recording(self):
        if self._is_on:
            self._is_recording = True
        else:
            raise Exception("Camera is off")
    
    def stop_recording(self):
        self._is_recording = False

    def get_status(self):
        return f"Camera is {'ON' if self._is_on else 'OFF'}, recording is {'ON' if self._is_recording else 'OFF'}"

class TV(Device):
    def __init__(self, id, name):
        if not id or not name:
            raise ValueError("ID и имя обязательны")
        super().__init__(id, name)
        self._is_on = False
        self._current_channel = 1
        self._volume = 50
        self._max_channel = 30
    
    def turn_on(self):
        self._is_on = True
    
    def turn_off(self):
        self._is_on = False
    
    def get_status(self):
        status = "ON" if self._is_on else "OFF"
        return f"TV is {status}, chanel: {self._current_channel}, volume: {self._volume}"
    
    def change_channel(self, channel):
        if not self._is_on:
            raise Exception("Error: TV is OFF")
        if 1 <= channel <= self._max_channel:
            self._current_channel = channel
            return f"Канал изменен на {channel}"
        else:
            raise Exception("Error: channel must be between 1 and {self._max_channel}")
    
    def set_volume(self, volume):
        if not self._is_on:
            raise Exception("Error: TV is OFF")
        if 0 <= volume <= 100:
            self._volume = volume
            return f"Громкость установлена на {volume}"
        else:
            raise Exception("Error: volume must be between 1 and 100")
    
    @property
    def current_channel(self):
        return self._current_channel
    
    @property
    def volume(self):
        return self._volume
    
    @property
    def is_on(self):
        return self._is_on

class SmartHouse:
    def __init__(self):
        self._devices = {}

    def add_device(self, device):
        if (device.device_id in self._devices) == False:
            self._devices[device.device_id] = device
        else:
            raise Exception("You can not add same id multiple times")

    def remove_device(self, device_id):
        if device_id in self._devices:
            del self._devices[device_id]
        else:
            raise Exception("Device with this id is not exist")

    def find_device(self, device_id):
        if device_id in self._devices:
            return self._devices.get(device_id)
        else:
            raise Exception("There is no device with this id")
        
    def control_device(self, user, device_id, command, **kwargs):
        device = self.find_device(device_id)
        if device is None:
            raise Exception("Устройство не найдено")
        elif not user.has_permission(device, command):
            raise PermissionError("Недостаточно прав")
        else:
            return device.execute_command(command, **kwargs)
            
class User:
    def __init__(self, name, role:str):
        self._name = name
        self.__role = role
    
    def has_permission(self, device, command):
        if self.__role == 'ADMIN':
            return True
        elif self.__role == 'RESIDENT' and isinstance(device, (Light, Thermostat)):
            return True
        elif self.__role == 'GUEST' and isinstance(device, Light) and command in ['turn_on', 'turn_off']:
            return True
        else:
            return False