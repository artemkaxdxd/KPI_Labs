package com.example.first_app

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.Toast
import androidx.fragment.app.FragmentManager
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import java.io.File

class MainActivity : AppCompatActivity() {

    private lateinit var clAdapter : ChecklistAdapter

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val clValues = mutableListOf<Checklist>()
        clValues.add(Checklist("Cheese"))
        clValues.add(Checklist("Ketchup"))
        clValues.add(Checklist("Pepperoni"))
        clValues.add(Checklist("Tomatoes"))
        clValues.add(Checklist("Mushrooms"))

        clAdapter = ChecklistAdapter(clValues, mutableListOf())

        val checkListId = findViewById<RecyclerView>(R.id.rvChecklist)
        checkListId.adapter = clAdapter
        checkListId.layoutManager = LinearLayoutManager(this)

        val fragment = FirstFragment()
        val fm: FragmentManager = supportFragmentManager

        val path = applicationContext.filesDir
        val orderDirectory = File(path, "Orders")
        val fileName = "Order.txt"
        val file = File(orderDirectory, fileName)

        // Delete file before doing new orders
        file.delete()

        findViewById<Button>(R.id.btnSave).setOnClickListener{
            if(clAdapter.chosen.isNotEmpty()) {
                val order = clAdapter.chosen.joinToString { it }

                // Create dir and file with order
                orderDirectory.mkdirs()

                // Write order to file
                file.writeText(order)
                Toast.makeText(applicationContext, "Order saved to $fileName", Toast.LENGTH_LONG).show()

                // Send bundle msg to fragment
                val mBundle = Bundle()
                mBundle.putString("mText", order)
                fragment.arguments = mBundle
                fm.beginTransaction().add(R.id.flFragment, fragment).addToBackStack(null).commit()
            } else {
                Toast.makeText(applicationContext, "Select some items", Toast.LENGTH_LONG).show()
            }
        }

        findViewById<Button>(R.id.btnOpenFile).setOnClickListener{
            if (file.exists()) {
                val intent = Intent(applicationContext, Reader::class.java)
                startActivity(intent)
            } else {
                Toast.makeText(applicationContext, "$fileName does not exist, save some items first", Toast.LENGTH_LONG).show()
            }
        }
    }
}