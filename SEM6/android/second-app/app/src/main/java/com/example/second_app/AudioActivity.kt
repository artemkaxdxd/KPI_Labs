package com.example.second_app

import android.media.MediaPlayer
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button

class AudioActivity : AppCompatActivity() {

    private var mp: MediaPlayer? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_audio)

        controlSong(R.raw.wir_trinken)
    }

    private fun controlSong(id: Int) {
        findViewById<Button>(R.id.btnPlay).setOnClickListener{
            if (mp == null) {
                mp = MediaPlayer.create(this, id)
            }
            mp?.start()
        }

        findViewById<Button>(R.id.btnPause).setOnClickListener{
            if (mp !== null) mp?.pause()
        }

        findViewById<Button>(R.id.btnStop).setOnClickListener{
            if (mp !== null) {
                mp?.stop()
                mp?.reset()
                mp?.release()
                mp = null
            }
        }
    }
}