package com.example.third_app

import android.content.Context
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Vibrator
import android.widget.Toast

class MainActivity : AppCompatActivity(),SensorEventListener {
    var sensor: Sensor ?= null
    var sensorManager: SensorManager ?= null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        sensorManager = getSystemService(Context.SENSOR_SERVICE) as SensorManager
        sensor = sensorManager!!.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)
    }

    override fun onResume() {
        super.onResume()
        sensorManager!!.registerListener(this, sensor, SensorManager.SENSOR_DELAY_NORMAL)
    }

    override fun onPause() {
        super.onPause()
        sensorManager!!.unregisterListener(this)
    }

    var xStart = 0.0
    var yStart = 0.0
    var zStart = 0.0
    var threshold = 3000.0
    var startTime:Long = 0
    override fun onSensorChanged(event: SensorEvent?) {
        var x = event!!.values[0]
        var y = event!!.values[1]
        var z = event!!.values[2]
        var curTime = System.currentTimeMillis()

        if ((curTime - startTime) > 100) {
            var timeDiff = curTime - startTime
            startTime = curTime
            var speed = Math.abs(x+y+z-xStart-yStart-zStart) / timeDiff*10000

            if (speed > threshold) {
                var v = getSystemService(Context.VIBRATOR_SERVICE) as Vibrator
                v.vibrate(500)
                Toast.makeText(applicationContext, "device vibrated", Toast.LENGTH_LONG).show()

            }
        }
    }

    override fun onAccuracyChanged(p0: Sensor?, p1: Int) {
    }
}