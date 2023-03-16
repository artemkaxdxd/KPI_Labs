package com.example.lab_planner

import android.content.Context
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.recyclerview.widget.RecyclerView
import com.example.lab_planner.databinding.ActivitySubjectBinding

class SubjectActivity : AppCompatActivity() {

    lateinit var binding: ActivitySubjectBinding
    lateinit var taskAdapter: TaskAdapter
    lateinit var recyclerView: RecyclerView
    private val taskList = ArrayList<TaskModel>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivitySubjectBinding.inflate(layoutInflater)
        setContentView(binding.root)
        initialize()

        findViewById<Button>(R.id.btnAddTask).setOnClickListener {
            val fragmentAddTask = AddTaskFragment()
            addFragment(fragmentAddTask)
        }

        findViewById<Button>(R.id.btnDeleteTasks).setOnClickListener {
            taskAdapter.deleteTasks()
        }

        findViewById<Button>(R.id.btnDeleteSubject).setOnClickListener {
            if (taskAdapter.itemCount == 0) {
                // delete subject
            } else {
                Toast.makeText(applicationContext, "Cannot delete subject if there are still tasks to complete", Toast.LENGTH_LONG).show()
            }
        }

        val bundle = intent.extras
        if (bundle != null) {
            findViewById<TextView>(R.id.tvSubjName).text = bundle.getString("subjectName")
            findViewById<TextView>(R.id.tvSubjTaskType).text = bundle.getString("taskType")
        }
    }

    private fun initialize() {
        recyclerView = binding.rvLabs
        taskAdapter = TaskAdapter(setTask())
        recyclerView.adapter = taskAdapter
    }

    private fun addFragment(fragment: Fragment) {
        supportFragmentManager.beginTransaction()
            .replace(R.id.frAddTask, fragment)
            .addToBackStack(null)
            .commit()
    }

    private fun setTask(): ArrayList<TaskModel> {
        val task1 = TaskModel("Lab1", "03/04", "google class for info", false)
        taskList.add(task1)
        return taskList
    }

    fun addTask(taskName: String, deadline: String, misc: String) {
        taskList.add(TaskModel(taskName, deadline, misc, false))
    }
}