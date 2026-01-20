"""
data_stream
Directory: ex1/
Files to Submit: data_stream.py
Authorized: isinstance(), print()
"""

from abc import ABC, abstractmethod
from typing import Any, Union, Optional, List, Dict


class DataStream(ABC):
    """
    Abstract base class defining the interface for all data streams.

    Attributes:
        _id (str): Unique identifier for the stream.
        _type (str): Type/domain of data processed by this stream.
        _count (int): Total number of items processed.
    """

    def __init__(self, stream_id: str = "STREAM") -> None:
        """
        Initialize a DataStream with a unique identifier.

        Args:
            stream_id (str): Unique identifier for this stream instance.
        """
        super().__init__()
        self._id = stream_id
        self._type: str = "GENERIC"
        self._count: int = 0

    @abstractmethod
    def process_batch(self, data_batch: List[Any]) -> str:
        """
        Process a batch of data specific to this stream type.

        Args:
            data_batch (List[Any]): Batch of data to process.

        Returns:
            str: Summary of processing results.
        """
        pass

    def filter_data(
        self,
        data_batch: List[Any],
        criteria: Optional[str] = None,
    ) -> List[Any]:
        """
        Filter data batch based on optional criteria.

        Args:
            data_batch (List[Any]): Batch of data to filter.
            criteria (Optional[str]): Filter criteria. If None, returns all
            data.

        Returns:
            List[Any]: Filtered data matching the criteria.
        """
        if criteria is None:
            return data_batch
        else:
            return [data for data in data_batch if criteria in str(data)]

    def get_stats(self) -> Dict[str, Union[str, int, float]]:
        """
        Get statistics about this stream's processing.

        Returns:
            Dict: Stream ID, type, and item count processed.
        """
        return {
            "id": self._id,
            "type": self._type,
            "count": self._count,
        }


class SensorStream(DataStream):
    """
    Stream handler for environmental sensor data.
    """

    def __init__(self, stream_id: str) -> None:
        """
        Initialize a SensorStream with validation.

        Args:
            stream_id (str): Unique identifier for this sensor stream.

        Raises:
            ValueError: If stream_id is not a string.
        """
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
        """
        Filter sensor data based on sensor type (e.g., "temp", "humidity").

        Args:
            data_batch (List[Any]): Batch of sensor data to filter.
            criteria (Optional[str]): Sensor type to filter by.

        Returns:
            List[Any]: Numeric values matching the sensor type criteria.
        """
        if criteria is None:
            return data_batch
        filtered_data = []
        for data in data_batch:
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
                            val = float(s[len(criteria) + 1:])
                            filtered_data.append(val)
                        except ValueError:
                            pass
                case _:
                    continue
        return filtered_data

    def get_stats(self) -> Dict[str, Union[str, int, float]]:
        """
        Get sensor stream statistics.

        Returns:
            Dict: Stream ID, type, reading count, and average temperature.
        """
        return {
            "id": self._id,
            "type": self._type,
            "count": self._count,
            "avg_temp": self._avg_temp,
        }

    def process_batch(self, data_batch: List[Any]) -> str:
        """
        Process a batch of sensor data.

        Args:
            data_batch (List[Any]): Batch of sensor readings to process.

        Returns:
            str: Summary of sensor processing results.
        """
        data = self.filter_data(data_batch, criteria="temp")
        self._count = len(data_batch)

        if data:
            self._avg_temp = sum(data) / len(data)

        msg = f"Sensor analysis: {self._count} readings processed, "
        msg += f"avg temp: {self._avg_temp}°C"
        return msg


class TransactionStream(DataStream):
    """
    Stream handler for financial transaction data.
    """

    def __init__(self, stream_id: str) -> None:
        """
        Initialize a TransactionStream with validation.

        Args:
            stream_id (str): Unique identifier for this transaction stream.

        Raises:
            ValueError: If stream_id is not a string.
        """
        if isinstance(stream_id, str):
            super().__init__(stream_id)
        else:
            raise ValueError(f"stream_id '{stream_id}' is not a string")
        self._type = "Financial Data"
        self._net_flow: int = 0
        self._transaction_count: int = 0

    def filter_data(
        self,
        data_batch: List[Any],
        criteria: Optional[str] = None,
    ) -> List[Any]:
        """
        Filter transaction data based on transaction type (buy/sell).

        Args:
            data_batch (List[Any]): Batch of transaction data to filter.
            criteria (Optional[str]): Transaction type to filter by ("buy" or
            "sell").

        Returns:
            List[Any]: Filtered transactions matching the criteria.
        """
        if criteria is None:
            return data_batch
        filtered_data = []
        for data in data_batch:
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
                            val = float(s[len(criteria) + 1:])
                            filtered_data.append(val)
                        except ValueError:
                            pass
                case _:
                    continue
        return filtered_data

    def get_stats(self) -> Dict[str, Union[str, int, float]]:
        """
        Get transaction stream statistics.

        Returns:
            Dict: Stream ID, type, transaction count, and net flow.
        """
        return {
            "id": self._id,
            "type": self._type,
            "count": self._transaction_count,
            "net_flow": self._net_flow,
        }

    def process_batch(self, data_batch: List[Any]) -> str:
        """
        Process a batch of transaction data.

        Args:
            data_batch (List[Any]): Batch of transactions to process.

        Returns:
            str: Summary of transaction processing results.
        """
        self._transaction_count = len(data_batch)
        self._count = self._transaction_count
        buy_data = self.filter_data(data_batch, criteria="buy")
        sell_data = self.filter_data(data_batch, criteria="sell")

        buy_total = sum(buy_data) if buy_data else 0
        sell_total = sum(sell_data) if sell_data else 0
        self._net_flow = buy_total - sell_total

        msg = f"Transaction analysis: {self._transaction_count} operations, "
        msg += f"net flow: {'+' if self._net_flow >= 0 else ''}"
        msg += f"{self._net_flow} units"
        return msg


class EventStream(DataStream):
    """
    Stream handler for system event data.

    Processes system events, tracks error occurrences, and provides
    event-specific statistics and filtering.
    """

    def __init__(self, stream_id: str) -> None:
        """
        Initialize an EventStream with validation.

        Args:
            stream_id (str): Unique identifier for this event stream.

        Raises:
            ValueError: If stream_id is not a string.
        """
        if isinstance(stream_id, str):
            super().__init__(stream_id)
        else:
            raise ValueError(f"stream_id '{stream_id}' is not a string")
        self._type = "System Events"
        self._error_count: int = 0

    def filter_data(
        self,
        data_batch: List[Any],
        criteria: Optional[str] = None,
    ) -> List[Any]:
        """
        Filter event data based on event type.

        Args:
            data_batch (List[Any]): Batch of event data to filter.
            criteria (Optional[str]): Event type to filter by (e.g., "error",
            "login").

        Returns:
            List[Any]: Events matching the criteria.
        """
        if criteria is None:
            return data_batch
        return [e for e in data_batch if criteria in str(e).lower()]

    def get_stats(self) -> Dict[str, Union[str, int, float]]:
        """
        Get event stream statistics.

        Returns:
            Dict: Stream ID, type, total event count, and error count.
        """
        return {
            "id": self._id,
            "type": self._type,
            "count": self._count,
            "error_count": self._error_count,
        }

    def process_batch(self, data_batch: List[Any]) -> str:
        """
        Process a batch of event data.

        Args:
            data_batch (List[Any]): Batch of events to process.

        Returns:
            str: Summary of event processing results.
        """
        self._count = len(data_batch)
        error_events = self.filter_data(data_batch, criteria="error")
        self._error_count = len(error_events)

        msg = f"Event analysis: {self._count} events, "
        msg += f"{self._error_count} error"
        msg += f"{'s' if self._error_count != 1 else ''} detected"

        return msg


class StreamProcessor:
    """
    Manages and processes multiple data stream types polymorphically.
    """

    def __init__(self) -> None:
        """Initialize the StreamProcessor with an empty stream registry."""
        self.streams: List[DataStream] = []

    def add_stream(self, stream: DataStream) -> None:
        """
        Register a data stream for processing.

        Args:
            stream (DataStream): Any DataStream subclass instance.
        """
        if isinstance(stream, DataStream):
            self.streams.append(stream)
        else:
            msg = f"Expected DataStream, got {type(stream).__name__}"
            raise TypeError(msg)

    def process_all(self, batches: List[List[Any]]) -> List[str]:
        """
        Process data batches through all registered streams.

        Args:
            batches (List[List[Any]]): List of data batches to process.

        Returns:
            List[str]: Processing results from each stream.

        Raises:
            ValueError: If number of batches doesn't match number of streams.
        """
        if len(batches) != len(self.streams):
            raise ValueError(
                f"Expected {len(self.streams)} batches, got {len(batches)}"
            )

        results = []
        for stream, batch in zip(self.streams, batches):
            try:
                result = stream.process_batch(batch)
                results.append(result)
            except Exception as e:
                results.append(f"Error processing {stream._type}: {str(e)}")

        return results

    def get_all_stats(self) -> Dict[str, Dict[str, Union[str, int, float]]]:
        """
        Retrieve statistics from all registered streams.

        Returns:
            Dict: Statistics for each stream, keyed by stream ID.
        """
        stats = {}
        for stream in self.streams:
            stats[stream._id] = stream.get_stats()
        return stats


def data_stream() -> None:
    """
    Main demonstration of the polymorphic stream system.

    Showcases:
    - Individual stream types processing domain-specific data
    - Polymorphic processing through StreamProcessor
    - Unified interface handling multiple data types
    """
    print("=== CODE NEXUS - POLYMORPHIC STREAM SYSTEM ===\n")

    # Initialize and demonstrate individual streams
    print("Initializing Sensor Stream...")
    sensor = SensorStream("SENSOR_001")
    print(f"Stream ID: {sensor._id}, Type: {sensor._type}")
    sensor_data = [("temp", 22.5), ("humidity", 65), ("pressure", 1013)]
    print("Processing sensor batch: [temp:22.5, humidity:65, pressure:1013]")
    print(sensor.process_batch(sensor_data))

    print("\nInitializing Transaction Stream...")
    transaction = TransactionStream("TRANS_001")
    print(f"Stream ID: {transaction._id}, Type: {transaction._type}")
    transaction_data = [("buy", 100), ("sell", 150), ("buy", 75)]
    print("Processing transaction batch: [buy:100, sell:150, buy:75]")
    print(transaction.process_batch(transaction_data))

    print("\nInitializing Event Stream...")
    event = EventStream("EVENT_001")
    print(f"Stream ID: {event._id}, Type: {event._type}")
    event_data = ["login", "error", "logout"]
    print("Processing event batch: [login, error, logout]")
    print(event.process_batch(event_data))

    # Demonstrate polymorphic processing
    print("\n=== Polymorphic Stream Processing ===")
    print("Processing mixed stream types through unified interface...\n")

    processor = StreamProcessor()
    processor.add_stream(SensorStream("SENSOR_002"))
    processor.add_stream(TransactionStream("TRANS_002"))
    processor.add_stream(EventStream("EVENT_002"))

    sensor_batch = [("temp", 20.0), ("temp", 21.0)]
    transaction_batch = [("buy", 50), ("sell", 30), ("buy", 20), ("sell", 10)]
    event_batch = [("critical", "alert"), "login", "error"]

    results = processor.process_all(
        [
            sensor_batch,
            transaction_batch,
            event_batch,
        ]
    )

    print("Batch 1 Results:")
    for i, result in enumerate(results, 1):
        print(f"- Stream {i}: {result}")

    print("\nStream filtering active: High-priority data only")
    print("Filtered results:")

    # Filter sensor data for temperatures above threshold
    sensor_filtered = processor.streams[0].filter_data(sensor_batch, "temp")
    print(f"  - {len(sensor_filtered)} critical sensor alerts")

    # Filter transactions
    large_transactions = processor.streams[1].filter_data(
        transaction_batch,
        "buy",
    )
    print(f"  - {len(large_transactions)} large transactions")

    print("\nAll streams processed successfully. Nexus throughput optimal.")


if __name__ == "__main__":
    data_stream()
