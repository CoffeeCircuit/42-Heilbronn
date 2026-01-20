"""
stream_processor
Directory: ex0/
Files to Submit: stream_processor.py
Authorized: print(), isinstance()
"""

from abc import ABC, abstractmethod
from typing import Any, Optional


class DataProcessor(ABC):
    """
    Abstract base class defining the interface for all data processors.

    This class establishes a contract for concrete implementations to validate,
    process, and format different types of data through a polymorphic
    interface.

    Attributes:
        ptype (Optional[str]): The type/name of the processor (set by
        subclasses).
    """

    def __init__(self) -> None:
        super().__init__()
        self.ptype: Optional[str] = None

    @abstractmethod
    def process(self, data: Any) -> str:
        """
        Process the given data and return a string representation.

        Args:
            data (Any): The data to process. Type depends on concrete
            implementation.

        Returns:
            str: Processed data as a string, or empty string if validation
            fails.
        """
        pass

    @abstractmethod
    def validate(self, data: Any) -> bool:
        """
        Validate whether the data is in the correct format for processing.

        Args:
            data (Any): The data to validate.

        Returns:
            bool: True if data is valid for this processor, False otherwise.
        """
        pass

    def format_output(self, result: str) -> str:
        """
        Format the processed result for user-friendly display.

        Args:
            result (str): The processed result string.

        Returns:
            str: Formatted output string ready for presentation.
        """
        return f"Output: {result}"


class NumericProcessor(DataProcessor):
    """
    Concrete processor for handling numeric data (integers and lists of
    numbers).

    Validates that data is iterable and all elements can be converted to
    integers. Calculates count, sum, and average of the numeric values.
    """

    def __init__(self) -> None:
        super().__init__()
        self.ptype = "Numeric"

    def validate(self, data: Any) -> bool:
        """
        Validate that data is iterable and contains only numeric values.

        Args:
            data (Any): Data to validate (should be iterable of numbers).

        Returns:
            bool: True if all elements can be converted to integers, False
            otherwise.
        """
        try:
            [int(x) for x in data]
            return True
        except (ValueError, TypeError):
            return False

    def process(self, data: Any) -> str:
        """
        Process numeric data and calculate statistics.

        Args:
            data (Any): Iterable of numeric values.

        Returns:
            str: Colon-separated string of "count:sum:average", or empty
            string if invalid.
        """
        if not self.validate(data):
            return ""
        vals = [int(val) for val in data]
        return f"{len(vals)}:{sum(vals)}:{sum(vals) / len(vals)}"

    def format_output(self, result: str) -> str:
        """
        Format numeric processing results for display.

        Args:
            result (str): Processed result from process() method.

        Returns:
            str: Human-readable summary of numeric statistics.
        """
        if not result:
            return ""
        count, total, avg = result.split(":")
        msg = f"Processed {count} numeric values, sum={total}, avg={avg}"
        return msg


class TextProcessor(DataProcessor):
    """
    Concrete processor for handling plain text data.

    Validates that data is a non-empty string and is not a log message.
    Counts characters and words in the text.
    """

    def __init__(self) -> None:
        super().__init__()
        self.ptype = "Text"

    def validate(self, data: Any) -> bool:
        """
        Validate that data is a plain text string (not a log message).

        Args:
            data (Any): Data to validate.

        Returns:
            bool: True if data is a non-empty string without log prefixes,
            False otherwise.
        """
        try:
            if all(
                (
                    type(data) is str,
                    len(data) > 0,
                    data[:6] != "ERROR:",
                    data[:5] != "INFO:",
                )
            ):
                return True
            else:
                raise ValueError("data is not Text")
        except (ValueError, TypeError):
            return False

    def process(self, data: Any) -> str:
        """
        Process text data and calculate character and word counts.

        Args:
            data (Any): Text string to process.

        Returns:
            str: Colon-separated string of "character_count:word_count", or
            empty string if invalid.
        """
        if not self.validate(data):
            return ""
        return f"{len(data)}:{len(data.split())}"

    def format_output(self, result: str) -> str:
        """
        Format text processing results for display.

        Args:
            result (str): Processed result from process() method.

        Returns:
            str: Human-readable summary of text statistics.
        """
        if not result:
            return ""
        char_count, word_count = result.split(":")
        msg = f"Processed text: {char_count} characters, {word_count} words"
        return msg


class LogProcessor(DataProcessor):
    """
    Concrete processor for handling log message data.

    Validates that data is a string starting with "INFO:" or "ERROR:" prefixes.
    Classifies ERROR messages as ALERT level and formats them appropriately.
    """

    def __init__(self) -> None:
        super().__init__()
        self.ptype = "Log"

    def validate(self, data: Any) -> bool:
        """
        Validate that data is a properly formatted log message.

        Args:
            data (Any): Data to validate.

        Returns:
            bool: True if data is a string starting with "INFO:" or "ERROR:",
            False otherwise.
        """
        try:
            if type(data) is str:
                if all(
                    (
                        type(data) is str,
                        len(data) > 0,
                        data[:6] == "ERROR:" or data[:5] == "INFO:",
                    )
                ):
                    return True
                else:
                    raise ValueError("data is not a Log")
            else:
                raise ValueError("data is not a Log")
        except (ValueError, TypeError):
            return False

    def process(self, data: Any) -> str:
        """
        Process log message data and classify by severity level.

        Args:
            data (Any): Log message string to process.

        Returns:
            str: Colon-separated string of "level:message", where level is
            INFO or ALERT.
        """
        log_t = "INFO"
        if not self.validate(data):
            return ""
        if data[:6] == "ERROR:":
            log_t = "ALERT"
        return f"{log_t}:{data}"

    def format_output(self, result: str) -> str:
        """
        Format log processing results for display with severity indicators.

        Args:
            result (str): Processed result from process() method.

        Returns:
            str: Formatted log message with [ALERT] or [INFO] brackets and l
            evel classification.
        """
        msg = ""
        if not result:
            return ""
        log_t, log_msg = result.split(":", 1)
        if log_t == "ALERT":
            msg = f"[ALERT] {log_msg[:5]} level detected: {log_msg[6:]}"
        elif log_t == "INFO":
            msg = f"[INFO] {log_msg[:4]} level detected: {log_msg[6:]}"
        return msg


def run_process(proc: DataProcessor, data: Any) -> None:
    """
    Execute data processing through a unified interface.

    Validates the data using the provided processor and outputs formatted
    results. This function demonstrates polymorphic behavior by working with
    any DataProcessor subclass without knowing its specific type.

    Args:
        proc (DataProcessor): Any concrete DataProcessor instance.
        data (Any): Data to process (type depends on processor).
    """
    if proc.validate(data):
        result = proc.process(data)
        print(proc.format_output(result))


def stream_processor() -> None:
    """
    Main demonstration function showcasing the polymorphic processor framework.

    Demonstrates:
    - Individual processor functionality with specific data types
    - Polymorphic interface allowing unified handling of different processors
    - The power of method overriding in enabling flexible, extensible designs
    """
    print("=== CODE NEXUS - DATA PROCESSOR FOUNDATION ===")

    print("\nInitializing Numeric Processor...")
    nproc = NumericProcessor()
    ndata = [1, 2, 3, 4, 5]
    print(f"Processing data: {ndata}")
    if nproc.validate(ndata):
        print("Validation: ", nproc.ptype, "data verified")
        print("Output: ", end="")
        print(nproc.format_output(nproc.process(ndata)))
    else:
        print("Validation: ", nproc.ptype, "data invalid")

    print("\nInitializing Text Processor...")
    tproc = TextProcessor()
    tdata = "Hello Nexus World"
    print(f'Processing data: "{tdata}"')
    if tproc.validate(tdata):
        print("Validation: ", tproc.ptype, "data verified")
        print("Output: ", end="")
        print(tproc.format_output(tproc.process(tdata)))
    else:
        print("Validation: ", tproc.ptype, "data invalid")

    print("\nInitializing Log Processor...")
    lproc = LogProcessor()
    ldata = "ERROR: Connection timeout"
    print(f'Processing data: "{ldata}"')
    if lproc.validate(ldata):
        print("Validation: ", lproc.ptype, "data verified")
        print("Output: ", end="")
        print(lproc.format_output(lproc.process(ldata)))
    else:
        print("Validation: ", lproc.ptype, "data invalid")

    print("\n=== Polymorphic Processing Demo ===")
    print("Processing multiple data types through same interface...")
    i = 1
    for data in (
        [0, 2, 4],
        "The quick brown fox",
        "INFO: System ready",
    ):
        for processor in (NumericProcessor(), TextProcessor(), LogProcessor()):
            if processor.validate(data):
                print(f"Result {i}: ", end="")
                run_process(processor, data)
                i += 1


if __name__ == "__main__":
    stream_processor()
