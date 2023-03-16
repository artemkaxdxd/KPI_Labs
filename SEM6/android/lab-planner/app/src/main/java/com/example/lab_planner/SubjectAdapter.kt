package com.example.lab_planner

import android.content.Context
import android.content.Intent
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.core.content.ContextCompat.startActivity
import androidx.recyclerview.widget.RecyclerView

class SubjectAdapter(): RecyclerView.Adapter<SubjectAdapter.SubjectViewHolder>() {


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

        val context = holder.itemView.findViewById<TextView>(R.id.tvName).context
        val bundle = Bundle()
        bundle.putString("subjectName", subjectList[position].subjectName)
        bundle.putString("taskType", subjectList[position].taskType)

        holder.itemView.setOnClickListener {
            context.startActivity(Intent(context, SubjectActivity::class.java).putExtras(bundle))
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