export interface ReadingsDataInterface {
  "readings": {
    [key: string]: {
      humidity: number,
      pressure: number,
      temperature: number,
      timestamp: string
    }
  }
}
