package com.example.first_app

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.CheckBox
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class ChecklistAdapter(
    private val items: MutableList<Checklist>,
    val chosen: MutableList<String>
) : RecyclerView.Adapter<ChecklistAdapter.ChecklistViewHolder>() {

    class ChecklistViewHolder(ItemView: View) : RecyclerView.ViewHolder(ItemView)

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ChecklistViewHolder {
        return ChecklistViewHolder(
            LayoutInflater.from(parent.context).inflate(
                R.layout.item_checkbox,
                parent,
                false
            )
        )
    }

    private fun saveItem (tvCheckListTitle: TextView, isChecked: Boolean) {
        if (isChecked) {
            chosen.add(tvCheckListTitle.text.toString())
        } else {
            chosen.remove(tvCheckListTitle.text.toString())
        }
    }

    override fun onBindViewHolder(holder: ChecklistViewHolder, position: Int) {
        val curItem = items[position]
        holder.itemView.apply {
            findViewById<TextView>(R.id.tvChecklistTitle).text = curItem.title
            findViewById<CheckBox>(R.id.cbChose).isChecked = curItem.isChecked

            findViewById<CheckBox>(R.id.cbChose).setOnCheckedChangeListener{_, isChecked ->
                saveItem(findViewById(R.id.tvChecklistTitle), isChecked)
                curItem.isChecked = !curItem.isChecked
            }
        }

    }

    override fun getItemCount(): Int {
        return items.size
    }
}