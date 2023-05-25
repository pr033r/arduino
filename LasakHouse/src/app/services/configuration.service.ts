import {Injectable} from '@angular/core';
import {Chart, registerables} from 'chart.js';

Chart.register(...registerables);

@Injectable({
  providedIn: 'root'
})
export class ConfigurationService {

  public readonly numberOfValuesToShow = 10;

  public tempHumChartConfig(labels: Array<string>, temp: Array<number>, hum: Array<number>) {
    return new Chart('LineChart', {
      type: 'line',
      data: {
        labels: labels,
        datasets: [
          {
            label: "Teplota",
            data: temp,
            borderColor: 'lightBlue',
            backgroundColor: 'SteelBlue',
            pointStyle: 'circle',
            pointRadius: 10,
            pointHoverRadius: 15
          },
          {
            label: "Vlhkost",
            data: hum,
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

  constructor() {
  }
}
