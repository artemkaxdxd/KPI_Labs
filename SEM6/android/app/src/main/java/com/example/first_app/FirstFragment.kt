package com.example.first_app

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment

class FirstFragment : Fragment(R.layout.fragment_first) {
    private lateinit var myTextView: TextView

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View {
        val view: View = inflater.inflate(R.layout.fragment_first, container, false)
        myTextView = view.findViewById<View>(R.id.tvFragment) as TextView
        val bundle = arguments
        val message = bundle!!.getString("mText")
        myTextView.text = message
        return view
    }
}