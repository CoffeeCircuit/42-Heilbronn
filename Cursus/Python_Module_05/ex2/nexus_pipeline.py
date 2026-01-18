"""
nexus_pipeline
Directory: ex2/
Files to Submit: nexus_pipeline.py
Authorized: isinstance(), print(), collections
"""

from abc import ABC, abstractmethod
from typing import Protocol, runtime_checkable
from typing import Any, Union, Optional, List, Dict


@runtime_checkable
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


class ProcessingPipeline(ABC):
    def __init__(self) -> None:
        super().__init__()
        self.stages: List[ProcessingStage] = []

    @abstractmethod
    def process(self, data: Any) -> Any:
        pass

    def add_stage(self, stage: ProcessingStage):
        if not isinstance(stage, ProcessingStage):
            raise TypeError("Stage must implement process()")
        self.stages.append(stage)


class JSONAdapter(ProcessingPipeline):
    def __init__(self, pipeline_id) -> None:
        super().__init__()
        self._id = pipeline_id

    def process(self, data: Any) -> Any:
        step = data
        for stage in self.stages:
            try:
                step = stage.process(step)
            except Exception as e:
                print(f"Error in stage {stage.__class__.__name__}: {e}")
        return step


class CSVAdapter(ProcessingPipeline):
    def __init__(self, pipeline_id) -> None:
        super().__init__()
        self._id = pipeline_id

    def process(self, data: Any) -> Any:
        step = data
        for stage in self.stages:
            try:
                step = stage.process(step)
            except Exception as e:
                print(f"Error in stage {stage.__class__.__name__}: {e}")
        return step


class StreamAdapter(ProcessingPipeline):
    def __init__(self, pipeline_id) -> None:
        super().__init__()
        self._id = pipeline_id

    def process(self, data: Any) -> Any:
        step = data
        for stage in self.stages:
            try:
                step = stage.process(step)
            except Exception as e:
                print(f"Error in stage {stage.__class__.__name__}: {e}")
        return step


class NexusManager:
    def __init__(self) -> None:
        self.pipelines: List[ProcessingPipeline] = []

    def add_pipeline(self, pipeline: ProcessingPipeline):
        if not isinstance(pipeline, ProcessingPipeline):
            raise TypeError("Invalid pipeline")
        self.pipelines.append(pipeline)

    def process_data(self, data: Any) -> Any:
        result = data
        for pipeline in self.pipelines:
            try:
                result = pipeline.process(result)
            except Exception as e:
                print(f"Error processing {pipeline}: {e}")
        return result
