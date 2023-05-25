import {Injectable} from '@angular/core';
import {AngularFireDatabase, AngularFireList, AngularFireObject} from "@angular/fire/compat/database";
import {ReadingsDataInterface} from "../models/readings-data.interface";

@Injectable({
  providedIn: 'root'
})
export class DataAccessService {

  private data!: AngularFireList<ReadingsDataInterface>;

  constructor(private db: AngularFireDatabase) {
  }

  fetchAll() {
    this.data = this.db.list('UsersData');
    return this.data.valueChanges();
  }
}
