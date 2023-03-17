package com.example.lab_planner

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import java.io.File

class AddSubjectFragment : Fragment() {
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val view: View = inflater!!.inflate(R.layout.fragment_add_subject, container, false)

        val subjName = view.findViewById<EditText>(R.id.etSubjectName).text
        val subjTaskType = view.findViewById<EditText>(R.id.etTaskType).text
        val context = view.findViewById<EditText>(R.id.etSubjectName).context

        view.findViewById<Button>(R.id.btnSaveSubject).setOnClickListener {

            if (subjName.toString().isNotEmpty() && subjTaskType.toString().isNotEmpty()) {
                (activity as MainActivity?)!!.addSubject(subjName.toString(), subjTaskType.toString())
                Toast.makeText(context, "Saved subject: $subjName", Toast.LENGTH_SHORT).show()

                view.findViewById<EditText>(R.id.etSubjectName).text.clear()
                view.findViewById<EditText>(R.id.etTaskType).text.clear()
            } else {
                Toast.makeText(context, "Enter data in all fields", Toast.LENGTH_SHORT).show()
            }
        }
        return view
    }

}