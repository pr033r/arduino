import {Component, OnDestroy, OnInit} from '@angular/core';
import {Chart, registerables} from 'chart.js';
import {ReadingsDataInterface} from "../../services/readings-data.interface";
import {Subscription} from "rxjs";
import {DataAccessService} from "../../services/data-access.service";
import {MeasurementDataDataInterface} from "../../services/measurement-data-data.interface";

Chart.register(...registerables);

@Component({
  selector: 'app-line-chart',
  templateUrl: './line-chart.component.html',
  styleUrls: ['./line-chart.component.scss']
})
export class LineChartComponent implements OnInit, OnDestroy {
  temperatureChart: any;
  private dataSubscription!: Subscription;
  numberOfValuesToShow = 24;
  measurementData: Array<MeasurementDataDataInterface> = [];
  lastElements: Array<MeasurementDataDataInterface> = []

  constructor(private dataAccess: DataAccessService) {
  }

  ngOnInit() {
    this.dataSubscription = this.dataAccess.fetchAll().subscribe(data => {

      this.extractFirebaseData(data);
      this.createTemperatureChart();
    })
  }

  ngOnDestroy() {
    this.dataSubscription.unsubscribe();
  }

  private createTemperatureChart() {
    this.lastElements = this.measurementData.slice(-this.numberOfValuesToShow);
    const dateLabels = this.lastElements.map(x => x.timestamp);
    const humidity = this.lastElements.map(x => x.humidity);
    const temperature = this.lastElements.map(x => x.temperature);

    this.temperatureChart = new Chart('TemperatureChart', {
      type: 'line',
      data: {
        labels: dateLabels,
        datasets: [
          {
            label: "Teplota",
            data: temperature,
            borderColor: 'lightBlue',
            backgroundColor: 'SteelBlue',
            pointStyle: 'circle',
            pointRadius: 10,
            pointHoverRadius: 15
          },
          {
            label: "Vlhkost",
            data: humidity,
            borderColor: 'LightCoral',
            backgroundColor: 'IndianRed',
            pointStyle: 'circle',
            pointRadius: 10,
            pointHoverRadius: 15
          }
        ]
      },
      options: {
        aspectRatio: 4.5,
        responsive: true,
      }
    });
  }

  private extractFirebaseData(firebaseData: Array<ReadingsDataInterface>) {
    if (firebaseData[0].readings) {
      for (let key in firebaseData[0].readings) {
        if (!firebaseData[0].readings.hasOwnProperty(key)) continue;

        const obj = firebaseData[0].readings[key];
        this.measurementData.push({
          humidity: obj.humidity,
          temperature: obj.temperature,
          pressure: obj.pressure,
          timestamp: this.convertTimestampToDate(obj.timestamp)
        });
      }
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
