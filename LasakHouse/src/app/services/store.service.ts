import {Injectable} from '@angular/core';
import {MeasurementDataDataInterface} from "../models/measurement-data-data.interface";
import {BehaviorSubject} from "rxjs";
import {ReadingsDataInterface} from "../models/readings-data.interface";

@Injectable({
  providedIn: 'root'
})
export class StoreService {

  private measuredDataSource: BehaviorSubject<Array<MeasurementDataDataInterface>>
    = new BehaviorSubject<Array<MeasurementDataDataInterface>>([]);

  measuredData = this.measuredDataSource.asObservable();

  constructor() {
  }

  setMeasuredData(data: Array<MeasurementDataDataInterface>) {
    this.measuredDataSource.next(data);
  }

  extractFirebaseData(firebaseData: Array<ReadingsDataInterface>) {
    const extractMeasuredData: Array<MeasurementDataDataInterface> = [];
    const firebaseReadings = firebaseData[0].readings;
    if (firebaseReadings) {
      for (let key in firebaseReadings) {
        if (!firebaseReadings.hasOwnProperty(key)) continue;

        const obj = firebaseReadings[key];
        extractMeasuredData.push({
          humidity: obj.humidity,
          temperature: obj.temperature,
          pressure: obj.pressure,
          timestamp: this.convertTimestampToDate(obj.timestamp)
        });
      }
      this.setMeasuredData(extractMeasuredData);
    }
  }

  private convertTimestampToDate(timestamp: string) {
    const date = new Date(parseInt(timestamp) * 1000);
    const day = date.getDate();
    const month = date.getMonth() + 1;
    const hours = date.getHours();
    const minutes = date.getMinutes();
    return `${day}.${month}. [${hours}:${minutes}]`;
  }
}
