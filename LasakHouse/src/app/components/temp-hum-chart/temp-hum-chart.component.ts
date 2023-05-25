import { Component, OnDestroy, OnInit } from '@angular/core';
import { Chart, registerables } from 'chart.js';
import { Subscription } from 'rxjs';
import { DataAccessService } from '../../services/data-access.service';
import { MeasurementDataDataInterface } from '../../models/measurement-data-data.interface';
import { StoreService } from '../../services/store.service';
import { ConfigurationService } from '../../services/configuration.service';

Chart.register(...registerables);

@Component({
  selector: 'app-temp-hum-chart',
  templateUrl: './temp-hum-chart.component.html',
  styleUrls: ['./temp-hum-chart.component.scss'],
})
export class TempHumChartComponent implements OnInit, OnDestroy {
  temperatureChart: any;
  actualMeasurement: MeasurementDataDataInterface = {
    humidity: 0,
    pressure: 0,
    temperature: 0,
    timestamp: '',
  };
  private firebaseDataSubscription!: Subscription;
  private extractedDataSubscription!: Subscription;

  constructor(
    private dataAccess: DataAccessService,
    private store: StoreService,
    private conf: ConfigurationService
  ) {}

  ngOnInit() {
    this.firebaseDataSubscription = this.dataAccess
      .fetchAll()
      .subscribe((data) => {
        this.store.extractFirebaseData(data);
        this.createTemperatureChart();
      });
  }

  ngOnDestroy() {
    this.firebaseDataSubscription.unsubscribe();
    this.extractedDataSubscription.unsubscribe();
  }

  private createTemperatureChart() {
    this.extractedDataSubscription = this.store.measuredData.subscribe(
      (data) => {
        const lastValues = data.slice(-this.conf.numberOfValuesToShow);
        const labels = lastValues.map((x) => x.timestamp);
        const hum = lastValues.map((x) => x.humidity);
        const temp = lastValues.map((x) => x.temperature);

        this.actualMeasurement = lastValues[this.conf.numberOfValuesToShow - 1];
        this.temperatureChart = this.conf.tempHumChartConfig(labels, temp, hum);
      }
    );
  }
}
