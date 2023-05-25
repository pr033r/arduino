import {MeasurementDataDataInterface} from "./measurement-data-data.interface";

export interface ReadingsDataInterface {
  "readings": {
    [key: string]: MeasurementDataDataInterface
  }
}
