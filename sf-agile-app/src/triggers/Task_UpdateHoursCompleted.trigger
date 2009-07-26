trigger Task_UpdateHoursCompleted on Task__c (before update) {
    List <TaskEffort__c> taskEffortList = [
        select Id, 
               Hours__c, 
               Status__c,
               Task__c
          from TaskEffort__c 
         where Task__c in : Trigger.newMap.keySet ()
    ];
    
    //
    // Reset hours completed to 0
    //
    
    for(Task__c task : Trigger.new)
        task.HoursCompleted__c = 0;
    
    //
    // Increment new hours
    //
    
    for(TaskEffort__c taskEffort : taskEffortList) {
        if (Trigger.newMap.containsKey (taskEffort.Task__c) == false)
            continue;
        if (taskEffort.Hours__c <= 0)
            continue;
            
        Task__c task = Trigger.newMap.get (taskEffort.Task__c);
        task.HoursCompleted__c += taskEffort.Hours__c;
    }

}