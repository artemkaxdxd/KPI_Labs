package com.example.second_app

import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.MediaController
import android.widget.VideoView

class VideoActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_video)

        val mediaController = MediaController(this)
        mediaController.setAnchorView(findViewById<VideoView>(R.id.videoView))

        val onlineUri = Uri.parse("https://joy1.videvo.net/videvo_files/video/free/2014-12/large_watermarked/Raindrops_Videvo_preview.mp4")
        val offlineUri = Uri.parse("android.resource://$packageName/${R.raw.dog}")

        findViewById<Button>(R.id.btnOffline).setOnClickListener{
            findViewById<VideoView>(R.id.videoView).apply {
                setMediaController(mediaController)
                setVideoURI(offlineUri)
                requestFocus()
                start()
            }
        }
        findViewById<Button>(R.id.btnOnline).setOnClickListener{
            findViewById<VideoView>(R.id.videoView).apply {
                setMediaController(mediaController)
                setVideoURI(onlineUri)
                requestFocus()
                start()
            }
        }
    }
}