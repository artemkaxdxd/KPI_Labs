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
    private lateinit var db: Database
    lateinit var recyclerView: RecyclerView
    lateinit var subjAdapter: SubjectAdapter

    private lateinit var subjName: String
    private lateinit var taskType: String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivitySubjectBinding.inflate(layoutInflater)

        db = Database(this)

        setContentView(binding.root)
        val bundle = intent.extras
        if (bundle != null) {
            findViewById<TextView>(R.id.tvSubjName).text = "Subject: " + bundle.getString("subjectName")
            subjName = bundle.getString("subjectName").toString()
            findViewById<TextView>(R.id.tvSubjTaskType).text = "Type of tasks: " + bundle.getString("taskType")
            taskType = bundle.getString("taskType").toString()
        }
        initialize()

        findViewById<Button>(R.id.btnAddTask).setOnClickListener {
            val fragmentAddTask = AddTaskFragment()
            addFragment(fragmentAddTask)
        }

        findViewById<Button>(R.id.btnDeleteTasks).setOnClickListener {
            taskAdapter.deleteTasks(subjName, taskType, db)
        }

        findViewById<Button>(R.id.btnDeleteSubject).setOnClickListener {
            if (taskAdapter.itemCount == 0) {
                db.deleteSubject(subjName, taskType)

                finish()
            } else {
                Toast.makeText(applicationContext, "Cannot delete subject if there are still tasks to complete", Toast.LENGTH_LONG).show()
            }
        }
    }

    private fun initialize() {
        recyclerView = binding.rvLabs
        taskAdapter = TaskAdapter(getTask())
        recyclerView.adapter = taskAdapter
    }

    private fun addFragment(fragment: Fragment) {
        supportFragmentManager.beginTransaction()
            .replace(R.id.frAddTask, fragment)
            .addToBackStack(null)
            .commit()
    }

    fun addTask(taskName: String, deadline: String, misc: String) {
        db.addDataTask(taskName, deadline, misc, subjName, taskType)
        taskAdapter.setTaskList(getTask())
    }

    private fun getTask(): ArrayList<TaskModel> {
        return db.getArrayListOfTasks(subjName)
    }
}