trigger TaskEffort_UpdateTask on TaskEffort__c (after delete, after insert, after update) {
    //
    // Build a list of parent tasks
    //
    
    List <Id> taskIds = new List <Id> ();
    List <TaskEffort__c> tasks;
    
    if (Trigger.isInsert || Trigger.isUpdate)
        tasks = Trigger.new;
    else
        tasks = Trigger.old;

    for(TaskEffort__c taskEffort : tasks)
        taskIds.add (taskEffort.Task__c);

    //
    // Fetch the parent tasks
    //
    
    update [
        select Id, HoursCompleted__c
          from Task__c
         where Id in : taskIds
    ];

}