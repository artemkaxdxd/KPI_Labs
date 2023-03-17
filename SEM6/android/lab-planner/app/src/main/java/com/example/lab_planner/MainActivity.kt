package com.example.lab_planner

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.RecyclerView
import com.example.lab_planner.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    lateinit var binding: ActivityMainBinding
    lateinit var subjAdapter: SubjectAdapter
    lateinit var recyclerViewSubj: RecyclerView

    private lateinit var db: Database

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        db = Database(this)

        // Delete database:
        // db.onUpgrade(db.writableDatabase, 1, 2)

        setContentView(binding.root)

        initialize()

        findViewById<Button>(R.id.btnAddSubject).setOnClickListener {
            val fragmentAddSubject = AddSubjectFragment()
            addFragment(fragmentAddSubject)
        }
    }

    override fun onResume() {
        super.onResume()
        subjAdapter.setList(getSubject())
    }

    private fun initialize() {
        recyclerViewSubj = binding.rvSubj
        subjAdapter = SubjectAdapter()
        recyclerViewSubj.adapter = subjAdapter
        subjAdapter.setList(getSubject())
    }

    private fun addFragment(fragment: Fragment) {
        supportFragmentManager.beginTransaction()
            .replace(R.id.frAddSubject, fragment)
            .addToBackStack(null)
            .commit()
    }

    fun addSubject(subjectName: String, taskType: String) {
        db.addDataSubject(subjectName, taskType)
        subjAdapter.setList(getSubject())
    }

    private fun getSubject(): ArrayList<SubjectModel> {
        return db.getArrayListOfSubjects()
    }
}