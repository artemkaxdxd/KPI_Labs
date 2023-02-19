package com.example.first_app

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.Toast
import androidx.fragment.app.FragmentManager
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

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

        val fragment = FirstFragment()
        val fm: FragmentManager = supportFragmentManager

        checkListId.adapter = clAdapter
        checkListId.layoutManager = LinearLayoutManager(this)

        findViewById<Button>(R.id.btnSave).setOnClickListener{
            if(clAdapter.chosen.isNotEmpty()) {
                val mBundle = Bundle()
                mBundle.putString("mText", clAdapter.chosen.joinToString { it })
                fragment.arguments = mBundle
                fm.beginTransaction().add(R.id.flFragment, fragment).addToBackStack(null).commit()

            } else {
                Toast.makeText(applicationContext, "Select some items", Toast.LENGTH_LONG).show()
            }
        }
    }
}