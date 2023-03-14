package com.example.lab_planner

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.recyclerview.widget.RecyclerView
import com.example.lab_planner.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    lateinit var binding: ActivityMainBinding
    lateinit var adapter: SubjectAdapter
    lateinit var recyclerView: RecyclerView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        initialize()
    }

    private fun initialize() {
        recyclerView = binding.rvSubj
        adapter = SubjectAdapter()
        recyclerView.adapter = adapter
        adapter.setList(setSubject())
    }

    fun setSubject(): ArrayList<SubjectModel> {
        val subjList = ArrayList<SubjectModel>()

        val subject1 = SubjectModel("ASD", "labs", "3")
        subjList.add(subject1)

        return subjList
    }
}