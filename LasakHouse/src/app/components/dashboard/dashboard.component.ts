import {Component, OnInit} from '@angular/core';
import {map} from 'rxjs/operators';
import {BreakpointObserver, Breakpoints} from '@angular/cdk/layout';
import {DataAccessService} from "../../services/data-access.service";


@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.scss']
})
export class DashboardComponent implements OnInit {
  /** Based on the screen size, switch from standard to one column per row */
  cards = this.breakpointObserver.observe(Breakpoints.Handset).pipe(
    map(({matches}) => {
      if (matches) {
        return [
          {id: 1, title: 'Aktuální hodnoty v bytě', cols: 2, rows: 1},
          {id: 2, title: 'Aktuální vlhkost v bytě', cols: 2, rows: 1},
          {id: 3, title: 'Card 3', cols: 2, rows: 1},
          {id: 4, title: 'Card 4', cols: 2, rows: 1}
        ];
      }

      return [
        {id: 1, title: 'Aktuální hodnoty v bytě', cols: 2, rows: 1},
        {id: 2, title: 'Aktuální vlhkost v bytě', cols: 2, rows: 1},
        {id: 3, title: 'Card 3', cols: 2, rows: 1},
        {id: 4, title: 'Card 4', cols: 2, rows: 1}
      ];
    })
  );

  constructor(private breakpointObserver: BreakpointObserver, private dataAccess: DataAccessService) {
  }

  ngOnInit() {
    this.dataAccess.fetchAll();
  }
}
