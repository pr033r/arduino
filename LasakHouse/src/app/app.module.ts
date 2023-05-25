import {NgModule} from '@angular/core';
import {BrowserModule} from '@angular/platform-browser';

import {AppRoutingModule} from './app-routing.module';
import {AppComponent} from './app.component';
import {BrowserAnimationsModule} from '@angular/platform-browser/animations';
import {LayoutModule} from '@angular/cdk/layout';
import {MatToolbarModule} from '@angular/material/toolbar';
import {MatButtonModule} from '@angular/material/button';
import {MatSidenavModule} from '@angular/material/sidenav';
import {MatIconModule} from '@angular/material/icon';
import {MatListModule} from '@angular/material/list';
import {DashboardComponent} from './components/dashboard/dashboard.component';
import {MatGridListModule} from '@angular/material/grid-list';
import {MatCardModule} from '@angular/material/card';
import {MatMenuModule} from '@angular/material/menu';
import {AngularFireModule} from "@angular/fire/compat";
import {AngularFireDatabaseModule} from "@angular/fire/compat/database";
import { LineChartComponent } from './components/line-chart/line-chart.component';

const firebaseConfig = {
  apiKey: "AIzaSyBCNbJbdqDnV6pFd3DkNHEYMWmVbjs43PU",
  authDomain: "lasak-house.firebaseapp.com",
  databaseURL: "https://lasak-house-default-rtdb.europe-west1.firebasedatabase.app",
  projectId: "lasak-house",
  storageBucket: "lasak-house.appspot.com",
  messagingSenderId: "806446501291",
  appId: "1:806446501291:web:98821668f92f24835a56ee",
  measurementId: "G-E659ZBWT3R"
}

@NgModule({
  declarations: [
    AppComponent,
    DashboardComponent,
    LineChartComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    BrowserAnimationsModule,
    LayoutModule,
    MatToolbarModule,
    MatButtonModule,
    MatSidenavModule,
    MatIconModule,
    MatListModule,
    MatGridListModule,
    MatCardModule,
    MatMenuModule,
    AngularFireModule.initializeApp(firebaseConfig, 'lasak-house'),
    AngularFireDatabaseModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule {
}
