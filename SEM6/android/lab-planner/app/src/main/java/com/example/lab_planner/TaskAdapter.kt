package com.example.lab_planner

import android.database.sqlite.SQLiteDatabase
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.CheckBox
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class TaskAdapter(private var taskList: MutableList<TaskModel>): RecyclerView.Adapter<TaskAdapter.TaskViewHolder>() {
    class TaskViewHolder(view: View): RecyclerView.ViewHolder(view)

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): TaskViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.item_task, parent, false)
        return TaskViewHolder(view)
    }

    override fun onBindViewHolder(holder: TaskViewHolder, position: Int) {
        val curTask = taskList[position]

        holder.itemView.apply{
            findViewById<TextView>(R.id.tvTaskName).text = taskList[position].taskName
            findViewById<TextView>(R.id.tvDeadline).text = "Deadline: " + taskList[position].deadline
            findViewById<TextView>(R.id.tvTaskMisc).text = "Info: " + taskList[position].misc
            findViewById<CheckBox>(R.id.cbDone).isChecked = taskList[position].isChecked

            findViewById<CheckBox>(R.id.cbDone).setOnCheckedChangeListener {_, isChecked ->
                curTask.isChecked = !curTask.isChecked
            }
        }
    }

    override fun getItemCount(): Int {
        return taskList.size
    }

    fun deleteTasks(subjName: String, taskType: String, db: Database) {
        for (task in taskList) {
            if (task.isChecked) {
                db.deleteTask(task.taskName, task.deadline, subjName, taskType)
            }
        }
        taskList.removeAll { task ->
            task.isChecked
        }
        notifyDataSetChanged()
    }

    fun setTaskList(list: ArrayList<TaskModel>) {
        taskList = list
        notifyDataSetChanged()
    }
}
