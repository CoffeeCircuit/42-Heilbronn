from abc import ABC, abstractmethod
from typing import Any, Union, Optional


class DataProcessor(ABC):
    def __init__(self) -> None:
        super().__init__()
        self.ptype: Optional[str] = None

    @abstractmethod
    def process(self, data: Any) -> str:
        pass

    @abstractmethod
    def validate(self, data: Any) -> bool:
        pass

    def format_output(self, result: str) -> str:
        return f"Output: {result}"


class NumericProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__()
        self.ptype = "Numeric"

    def validate(self, data: Any) -> bool:
        try:
            [int(x) for x in data]
            return True
        except ValueError:
            return False

    def process(self, data: Any) -> str:
        if not self.validate(data):
            return ""
        vals = [int(val) for val in data]
        return f"{len(vals)}:{sum(vals)}:{sum(vals) / len(vals)}"

    def format_output(self, result: str) -> str:
        if not result:
            return ""
        count, total, avg = result.split(":")
        msg = f"Processed {count} numeric values, sum={total}, avg={avg}"
        return msg


class TextProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__()
        self.ptype = "Text"

    def validate(self, data: Any) -> bool:
        try:
            if type(data) is str:
                return True
            else:
                raise ValueError("data is not Text")
        except ValueError:
            return False

    def process(self, data: Any) -> str:
        if not self.validate(data):
            return ""
        return f"{len(data)}:{len(data.split())}"

    def format_output(self, result: str) -> str:
        if not result:
            return ""
        char_count, word_count = result.split(":")
        msg = f"Processed text: {char_count} characters, {word_count} words"
        return msg


class LogProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__()
        self.ptype = "Log"

    def validate(self, data: Any) -> bool:
        try:
            if type(data) is str:
                if data[:6] == "ERROR:" or data[:5] == "INFO:":
                    return True
                else:
                    raise ValueError("data is not a Log")
            else:
                raise ValueError("data is not a Log")
        except ValueError:
            return False

    def process(self, data: Any) -> str:
        log_t = "INFO"
        if not self.validate(data):
            return ""
        if data[:6] == "ERROR:":
            log_t = "ALERT"
        return f"{log_t}:{data}"

    def format_output(self, result: str) -> str:
        msg = ""
        if not result:
            return ""
        log_t, log_msg = result.split(":", 1)
        if log_t == "ALERT":
            msg = f"[ALERT] {log_msg[:5]} level detected: {log_msg[6:]}"
        elif log_t == "INFO":
            msg = f"[INFO] {log_msg[:5]} level detected: {log_msg[6:]}"
        return msg


def run_process(
    proc: Union[TextProcessor, NumericProcessor, LogProcessor], data: Any
) -> None:

    print(f"\nInitializing {proc.ptype} Processor...")
    print(f"Processing data: {data}")
    if proc.validate(data):
        print("Validation: ", f"{proc.ptype} data verified")
    else:
        print("Validation: ", f"{proc.ptype} data error")

    result = proc.process(data)
    print("Output: ", proc.format_output(result))


def stream_processor():

    print("=== CODE NEXUS - DATA PROCESSOR FOUNDATION ===")
    run_process(NumericProcessor(), [1, 2, 3, 4, 5])
    run_process(TextProcessor(), "Hello Nexus World")
    run_process(LogProcessor(), "ERROR: Connection timeout")

    print("\n=== Polymorphic Processing Demo ===")
    print("Processing multiple data types through same interface...")


if __name__ == "__main__":
    stream_processor()
