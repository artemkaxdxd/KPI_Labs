import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
@Injectable()
export class HttpService {
  constructor(private http: HttpClient) { }
  getUsers() {
    return this.http.get('assets/users.json');
  }
}
