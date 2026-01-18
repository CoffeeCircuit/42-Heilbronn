"""
data_stream
Directory: ex1/
Files to Submit: data_stream.py
Authorized: isinstance(), print()
"""

from abc import ABC, abstractmethod
from typing import Any, Union, Optional, List, Dict


class DataStream(ABC):
    def __init__(self, stream_id: str = "STREAM") -> None:
        super().__init__()
        self._id = stream_id
        self._type: str = "GENERIC"
        self._count: int = 0

    @abstractmethod
    def process_batch(self, data_batch: List[Any]) -> str:
        pass

    def filter_data(
        self,
        data_batch: List[Any],
        criteria: Optional[str] = None,
    ) -> List[Any]:
        if criteria is None:
            return data_batch
        else:
            return [data for data in data_batch if criteria in str(data)]

    def get_stats(self) -> Dict[str, Union[str, int, float]]:
        return {
            "id": self._id,
            "type": self._type,
            "count": self._count,
        }


class SensorStream(DataStream):
    def __init__(self, stream_id: str) -> None:
        if isinstance(stream_id, str):
            super().__init__(stream_id)
        else:
            raise ValueError(f"stream_id '{stream_id}' is not a string")
        self._type = "Environmental Data"
        self._avg_temp: float = 0.0

    def filter_data(
        self,
        data_batch: List[Any],
        criteria: Optional[str] = None,
    ) -> List[Any]:
        if criteria is None:
            return data_batch
        filtered_data = []
        for data in data_batch:
            self._count += 1
            match data:
                case (c, x) | [c, x]:
                    if c == criteria and isinstance(x, (int, float)):
                        filtered_data.append(x)
                case dict() as d:
                    if criteria in d and isinstance(d[criteria], (int, float)):
                        filtered_data.append(d[criteria])
                case str() as s:
                    if s.startswith(f"{criteria}:"):
                        try:
                            _val = float(s[len(criteria) + 1:])
                            filtered_data.append(_val)
                        except ValueError:
                            print(f"Ignored malformed string: {s}")
                case _:
                    continue
        return filtered_data

    def get_stats(self) -> Dict[str, Union[str, int, float]]:
        return {
            "id": self._id,
            "type": self._type,
            "count": self._count,
            "avg_temp": self._avg_temp,
        }

    def process_batch(self, data_batch: List[Any]) -> str:
        data = self.filter_data(data_batch, criteria="temp")
        try:
            self._avg_temp = sum(data) / len(data)
        except ZeroDivisionError:
            print(f"No temperature data found in batch: {data}")
        msg = f"Sensor analysis: {self._count} readings processed, "
        msg += f"avg temp: {self._avg_temp}°C"
        return msg


class TransactionStream(DataStream):
    def __init__(self, stream_id: str) -> None:
        if isinstance(stream_id, str):
            super().__init__(stream_id)
        else:
            raise ValueError(f"stream_id '{stream_id}' is not a string")
        self._type = "Financial Data"
        self._net_flow: int = 0

    def filter_data(
        self,
        data_batch: List[Any],
        criteria: Optional[str] = None,
    ) -> List[Any]:
        if criteria is None:
            return data_batch
        filtered_data = []
        for data in data_batch:
            self._count += 1
            match data:
                case (c, x) | [c, x]:
                    if c == criteria and isinstance(x, (int, float)):
                        filtered_data.append(x)
                case dict() as d:
                    if criteria in d and isinstance(d[criteria], (int, float)):
                        filtered_data.append(d[criteria])
                case str() as s:
                    if s.startswith(f"{criteria}:"):
                        try:
                            _val = float(s[len(criteria) + 1 :])
                            filtered_data.append(_val)
                        except ValueError:
                            print(f"Ignored malformed string: {s}")
                case _:
                    continue
        return filtered_data

    def get_stats(self) -> Dict[str, Union[str, int, float]]:
        return {
            "id": self._id,
            "type": self._type,
            "count": self._count,
            "avg_temp": self._avg_temp,
        }

    def process_batch(self, data_batch: List[Any]) -> str:
        data = self.filter_data(data_batch, criteria="temp")
        try:
            self._avg_temp = sum(data) / len(data)
        except ZeroDivisionError:
            print(f"No temperature data found in batch: {data}")
        msg = f"Sensor analysis: {self._count} readings processed, "
        msg += f"avg temp: {self._avg_temp}°C"
        return msg


def data_stream():
    print("=== CODE NEXUS - POLYMORPHIC STREAM SYSTEM ===\n")

    print("Initializing Sensor Stream...")
    ssensor = SensorStream("SENSOR_001")
    print(f"Stream ID: {ssensor._id}, Type: {ssensor._type}")
    print("Processing sensor batch: [temp:22.5, humidity:65, pressure:1013]")
    out = ssensor.process_batch([("temp", 22.5), "humidity:65", "pressure:101"])
    print(out)


if __name__ == "__main__":
    data_stream()
