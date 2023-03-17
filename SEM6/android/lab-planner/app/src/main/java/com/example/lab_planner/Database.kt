package com.example.lab_planner

import android.content.ContentValues
import android.content.Context
import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import android.provider.BaseColumns

class Database(context: Context) :
    SQLiteOpenHelper(context, DATABASE_NAME, null, DATABASE_VERSION) {

    private val SQL_CREATE_ENTRIES =
        "CREATE TABLE $TABLE_SUBJECTS (" +
                "${BaseColumns._ID} INTEGER PRIMARY KEY," +
                "$COLUMN_SUBJECT_NAME TEXT," +
                "$COLUMN_TASK_TYPE TEXT,"+
                "$COLUMN_LAB_COUNT INTEGER)"

    private val SQL_CREATE_ENTRIES2 =
        "CREATE TABLE $TABLE_TASKS (" +
                "${BaseColumns._ID} INTEGER PRIMARY KEY," +
                "$COLUMN_SUBJECT_TASK_NAME TEXT," +
                "$COLUMN_TASK_NAME TEXT," +
                "$COLUMN_DEADLINE TEXT," +
                "$COLUMN_MISC TEXT)"

    private val SQL_DELETE_ENTRIES = "DROP TABLE IF EXISTS $TABLE_SUBJECTS"
    private val SQL_DELETE_ENTRIES2 = "DROP TABLE IF EXISTS $TABLE_TASKS"

    override fun onCreate(db: SQLiteDatabase) {
        db.execSQL(SQL_CREATE_ENTRIES)
        db.execSQL(SQL_CREATE_ENTRIES2)
    }

    override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
        db.execSQL(SQL_DELETE_ENTRIES)
        db.execSQL(SQL_DELETE_ENTRIES2)
        onCreate(db)
    }

    fun addDataSubject(subjName: String, taskType: String) {
        val values = ContentValues()
        values.put(COLUMN_SUBJECT_NAME, subjName)
        values.put(COLUMN_TASK_TYPE, taskType)
        values.put(COLUMN_LAB_COUNT, 0)
        val db = this.writableDatabase
        db.insert(TABLE_SUBJECTS, null, values)
        db.close()
    }

    fun addDataTask(taskName: String, deadline: String, misc: String, subjName: String, taskType: String) {
        val values = ContentValues()
        values.put(COLUMN_SUBJECT_TASK_NAME, subjName)
        values.put(COLUMN_TASK_NAME, taskName)
        values.put(COLUMN_DEADLINE, deadline)
        values.put(COLUMN_MISC, misc)

        val db = this.writableDatabase
        db.insert(TABLE_TASKS, null, values)

        val cursor = db.rawQuery("SELECT $COLUMN_LAB_COUNT FROM $TABLE_SUBJECTS WHERE $COLUMN_SUBJECT_NAME=? and $COLUMN_TASK_TYPE=?", arrayOf(subjName, taskType))
        val colLabCount = cursor.getColumnIndexOrThrow(COLUMN_LAB_COUNT)
        val valuesToUpd = ContentValues()
        if(cursor.moveToFirst() && cursor.count >= 1){
            valuesToUpd.put(COLUMN_LAB_COUNT, cursor.getInt(colLabCount)+1)
        }

        db.update(TABLE_SUBJECTS, valuesToUpd, "$COLUMN_SUBJECT_NAME=? and $COLUMN_TASK_TYPE=?",
            arrayOf(subjName, taskType))

        db.close()
    }

    fun deleteSubject(subjName: String, taskType: String) {
        val db = this.writableDatabase
        db.delete(TABLE_SUBJECTS, "$COLUMN_SUBJECT_NAME=? and $COLUMN_TASK_TYPE=?",
            arrayOf(subjName, taskType))
        db.close()
    }

    fun deleteTask(taskName: String, deadline: String, subjName: String, taskType: String) {
        val db = this.writableDatabase
        db.delete(
            TABLE_TASKS, "$COLUMN_TASK_NAME=? and $COLUMN_DEADLINE=?",
            arrayOf(taskName, deadline))

        val cursor = db.rawQuery(
            "SELECT $COLUMN_LAB_COUNT FROM $TABLE_SUBJECTS WHERE $COLUMN_SUBJECT_NAME=? and $COLUMN_TASK_TYPE=?",
            arrayOf(subjName, taskType))
        val colLabCount = cursor.getColumnIndexOrThrow(COLUMN_LAB_COUNT)
        val valuesToUpd = ContentValues()

        if(cursor.moveToFirst() && cursor.count >= 1){
            valuesToUpd.put(COLUMN_LAB_COUNT, cursor.getInt(colLabCount)-1)
        }

        db.update(TABLE_SUBJECTS, valuesToUpd, "$COLUMN_SUBJECT_NAME=? and $COLUMN_TASK_TYPE=?",
            arrayOf(subjName, taskType))

        db.close()
    }

    private fun getData(tableName: String): Cursor? {
        val db = this.readableDatabase
        return db.rawQuery("SELECT * FROM $tableName", null)
    }

    fun getArrayListOfSubjects(): ArrayList<SubjectModel> {
        val array = arrayListOf<SubjectModel>()
        val cursor = getData(TABLE_SUBJECTS)
        if (cursor!!.moveToFirst()) {
            val colSubjectName = cursor.getColumnIndexOrThrow(COLUMN_SUBJECT_NAME)
            val colTaskType = cursor.getColumnIndexOrThrow(COLUMN_TASK_TYPE)
            val colLabCount = cursor.getColumnIndexOrThrow(COLUMN_LAB_COUNT)

            array.add(
                SubjectModel(
                    cursor.getString(colSubjectName),
                    cursor.getString(colTaskType),
                    cursor.getInt(colLabCount)
                )
            )

            while (cursor.moveToNext()) {
                array.add(
                    SubjectModel(
                        cursor.getString(colSubjectName),
                        cursor.getString(colTaskType),
                        cursor.getInt(colLabCount)
                    )
                )
            }
        }

        cursor.close()
        return array
    }

    fun getArrayListOfTasks(subjName: String): ArrayList<TaskModel> {
        val array = arrayListOf<TaskModel>()

        val db = this.readableDatabase

        val cursor = db.rawQuery("SELECT * FROM $TABLE_TASKS WHERE $COLUMN_SUBJECT_TASK_NAME=?", arrayOf(subjName))

        if (cursor!!.moveToFirst()) {
            val colTaskName = cursor.getColumnIndexOrThrow(COLUMN_TASK_NAME)
            val colDeadline = cursor.getColumnIndexOrThrow(COLUMN_DEADLINE)
            val colMisc = cursor.getColumnIndexOrThrow(COLUMN_MISC)

            array.add(
                TaskModel(
                    cursor.getString(colTaskName),
                    cursor.getString(colDeadline),
                    cursor.getString(colMisc),
                    false
                )
            )

            while (cursor.moveToNext()) {
                array.add(
                    TaskModel(
                        cursor.getString(colTaskName),
                        cursor.getString(colDeadline),
                        cursor.getString(colMisc),
                        false
                    )
                )
            }
        }

        cursor.close()
        return array
    }

    companion object {
        const val DATABASE_VERSION = 1
        const val DATABASE_NAME = "Subjects.db"
        const val TABLE_SUBJECTS = "subjects"
        const val COLUMN_SUBJECT_NAME = "subject_name"
        const val COLUMN_TASK_TYPE = "task_type"
        const val COLUMN_LAB_COUNT = "lab_count"

        const val TABLE_TASKS = "tasks"
        const val COLUMN_SUBJECT_TASK_NAME = "subject_task_name"
        const val COLUMN_TASK_NAME = "task_name"
        const val COLUMN_DEADLINE = "deadline"
        const val COLUMN_MISC = "misc"
    }

}