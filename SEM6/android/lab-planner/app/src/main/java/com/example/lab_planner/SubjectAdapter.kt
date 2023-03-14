package com.example.lab_planner

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class SubjectAdapter: RecyclerView.Adapter<SubjectAdapter.SubjectViewHolder>() {

    private var subjectList = emptyList<SubjectModel>()

    class SubjectViewHolder(view: View): RecyclerView.ViewHolder(view)

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): SubjectViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.item_subject, parent, false)
        return SubjectViewHolder(view)
    }

    override fun onBindViewHolder(holder: SubjectViewHolder, position: Int) {
        holder.itemView.findViewById<TextView>(R.id.tvName).text = subjectList[position].subjectName
        holder.itemView.findViewById<TextView>(R.id.tvTaskType).text = subjectList[position].taskType
        holder.itemView.findViewById<TextView>(R.id.tvLabsLeft).text = subjectList[position].labsLeft
        holder.itemView.setOnClickListener {

        }
    }

    override fun getItemCount(): Int {
        return subjectList.size
    }

    fun setList(list: List<SubjectModel>) {
        subjectList = list
        notifyDataSetChanged()
    }
}