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

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        initialize()

        findViewById<Button>(R.id.btnAddSubject).setOnClickListener {
            val fragmentAddSubject = AddSubjectFragment()
            // add a fragment to add a subject to the list
            addFragment(fragmentAddSubject)
        }

    }

    private fun addFragment(fragment: Fragment) {
        supportFragmentManager.beginTransaction()
            .replace(R.id.frAddSubject, fragment)
            .addToBackStack(null)
            .commit()
    }

    private fun initialize() {
        recyclerViewSubj = binding.rvSubj
        subjAdapter = SubjectAdapter()
        recyclerViewSubj.adapter = subjAdapter
        subjAdapter.setList(setSubject())
    }

    fun setSubject(): ArrayList<SubjectModel> {
        val subjList = ArrayList<SubjectModel>()

        val subject1 = SubjectModel("111", "labs", "1")
        subjList.add(subject1)

        val subject2 = SubjectModel("222", "labs", "2")
        subjList.add(subject2)

        val subject3 = SubjectModel("333", "labs", "3")
        subjList.add(subject3)

        val subject4 = SubjectModel("444", "labs", "4")
        subjList.add(subject4)

        return subjList
    }
}