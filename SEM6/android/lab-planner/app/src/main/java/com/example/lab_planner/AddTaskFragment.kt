package com.example.lab_planner

import android.os.Bundle
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.fragment.app.FragmentManager

class AddTaskFragment : Fragment() {
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val view: View = inflater!!.inflate(R.layout.fragment_add_task, container, false)

        val taskName = view.findViewById<EditText>(R.id.etTaskName).text
        val taskDeadline = view.findViewById<EditText>(R.id.etDeadline).text
        val taskMisc = view.findViewById<EditText>(R.id.etMisc).text
        val context = view.findViewById<EditText>(R.id.etTaskName).context

        view.findViewById<Button>(R.id.btnSaveTask).setOnClickListener {

            if (taskName.toString().isNotEmpty() && taskDeadline.toString().isNotEmpty() && taskMisc.toString().isNotEmpty()) {
                (activity as SubjectActivity?)!!.addTask(taskName.toString(), taskDeadline.toString(), taskMisc.toString())
                Toast.makeText(context, "Saved task: $taskName", Toast.LENGTH_SHORT).show()

                view.findViewById<EditText>(R.id.etTaskName).text.clear()
                view.findViewById<EditText>(R.id.etDeadline).text.clear()
                view.findViewById<EditText>(R.id.etMisc).text.clear()

            } else {
                Toast.makeText(context, "Enter data in all fields", Toast.LENGTH_SHORT).show()
            }
        }
        return view
    }
}