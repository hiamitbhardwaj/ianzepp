/**
 * Societies Discussion Board (OSS)
 *
 * Copyright (C) 2009 - 2010, Ian Zepp <ian.zepp@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

public with sharing class Comment_ShowTree {
    // private vars
    private ApexPages.StandardController controller;
    
    // constructor
    public Comment_ShowTree() {}

    public Comment_ShowTree(ApexPages.StandardController controller) {
        this.controller = controller;
    }

    //
    // Active comment
    //
    
    public Comment__c comment {
        set;
        get;
    }

    //
    // Variable to assign new reply text to an existing comment
    //
    
    public Comment__c commentReply {
    	set;
    	get;
    }

    //
    // Return the time the comment was created (in friendly format)
    //

    public String getCommentCreated() {
        return comment.CreatedDate.format();
    }

    //
    // Convenience helpers
    //

    public String getParam(String name) {
        return ApexPages.currentPage().getParameters().get(name);
    }

    //
    // Full comment list
    //
    
    public List<Comment__c> getCommentList() {
        return [
           select CreatedById
                , CreatedDate
                , Depth__c
                , Disliked__c
                , IsInlineEdit__c
                , Liked__c
                , Link__c
                , Score__c
                , Text__c
                , Type__c
             from Comment__c
        ];
    }

    //
    // Update the number of votes
    //
    
    public PageReference updateLiked() {
        insert new CommentVote__c(Comment__c = getParam('commentId'), Type__c = 'Liked');
        return null;
    }

    public PageReference updateDisliked() {
        insert new CommentVote__c(Comment__c = getParam('commentId'), Type__c = 'Disliked');
        return null;
    }
    
    public PageReference updateReported() {
        insert new CommentVote__c(Comment__c = getParam('commentId'), Type__c = 'Reported');
        return null;
    }
    
    public PageReference updateReplyStarted() {
    	commentReply = new Comment__c();
    	commentReply.Parent__c = getParam('commentId');
    	commentReply.IsInlineEdit__c = true;
        return null;
    }

    public PageReference updateReplySaved() {
        upsert commentReply;
        commentReply = [
           select CreatedById
                , CreatedDate
                , Depth__c
                , Disliked__c
                , IsInlineEdit__c
                , Liked__c
                , Link__c
                , Score__c
                , Text__c
                , Type__c
             from Comment__c
            where Id = :commentReply.Id
        ];
        return null;
    }

    public PageReference updateReplyCanceled() {
        commentReply = null;
        return null;
    }
}