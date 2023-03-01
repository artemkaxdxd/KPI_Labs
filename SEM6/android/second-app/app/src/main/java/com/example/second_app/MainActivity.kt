package com.example.second_app

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        findViewById<Button>(R.id.btnAudio).setOnClickListener{
            val intent = Intent(applicationContext, AudioActivity::class.java)
            startActivity(intent)
        }
        findViewById<Button>(R.id.btnVideo).setOnClickListener{
            val intent = Intent(applicationContext, VideoActivity::class.java)
            startActivity(intent)
        }
    }
}