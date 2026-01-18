"""
nexus_pipeline
Directory: ex2/
Files to Submit: nexus_pipeline.py
Authorized: isinstance(), print(), collections
"""

from abc import ABC, abstractmethod
from typing import Protocol
from typing import Any, Union, Optional, List, Dict


class ProcessingPipeline(ABC):
    pass

    @abstractmethod
    def process(self, data: Any) -> Any:
        pass

    def add_stage(self):
        pass


class ProcessingStage(Protocol):
    """Interface for stages"""

    def process(self, data: Any) -> Any:
        """Method requiered for all stages"""
        pass


class InputStage:
    def process(self, data: Any) -> Dict:
        """Method requiered for all stages"""
        pass


class TransformStage:
    def process(self, data: Any) -> Dict:
        """Method requiered for all stages"""
        pass


class OutputStage:
    def process(self, data: Any) -> str:
        """Method requiered for all stages"""
        pass


class SONAdapter(ProcessingPipeline):
    def __init__(self, pipeline_id) -> None:
        super().__init__()
        self._id = pipeline_id


class CSVAdapter(ProcessingPipeline):
    def __init__(self, pipeline_id) -> None:
        super().__init__()
        self._id = pipeline_id


class StreamAdapter(ProcessingPipeline):
    def __init__(self, pipeline_id) -> None:
        super().__init__()
        self._id = pipeline_id


class NexusManager:
    def add_pipeline():
        pass

    def process_data():
        pass
