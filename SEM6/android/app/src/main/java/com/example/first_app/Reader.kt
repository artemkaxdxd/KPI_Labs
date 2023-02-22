package com.example.first_app

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import java.io.File
import java.io.FileInputStream

class Reader : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_reader)

        val path = applicationContext.filesDir
        val orderDirectory = File(path, "Orders")
        val file = File(orderDirectory, "Order.txt")

        val inputAsString = FileInputStream(file).bufferedReader().use { it.readText() }
        findViewById<TextView>(R.id.tvReader).text = inputAsString
    }
}