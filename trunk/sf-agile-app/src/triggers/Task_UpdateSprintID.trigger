trigger Task_UpdateSprintID on Task__c (before insert, before update) {
    for(Task__c task : Trigger.new)
        task.Sprint__c = task.StorySprintID__c;
}