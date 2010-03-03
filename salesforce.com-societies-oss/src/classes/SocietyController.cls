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

public with sharing class SocietyController {
    // private vars
    private ApexPages.StandardController controller;
    
    // SocietyComment.component treats this class as a controller
    public SocietyController() {}

    // Society.page treats this class as an extension
    public SocietyController(ApexPages.StandardController controller) {
        this.controller = controller;
        this.selectedSociety = (Society__c) controller.getRecord();
    }

    //
    // Convenience helpers
    //

    public String getParam(String name) {
        return ApexPages.currentPage().getParameters().get(name);
    }

    //
    // Selected society
    //

    public Society__c selectedSociety {
        set;
        get;
    }

    //
    // Selected society top-level parent post
    //

    public SocietyComment__c selectedSocietyPost {
        set;
        get;
    }

    //
    // Selected society comment
    //

    public SocietyComment__c selectedSocietyComment {
        set;
        get;
    }

    //
    // Society methods
    //

    public List<Society__c> getSocietyList() {
        return [
           select Account__r.Name
                , Account__r.OwnerId
                , Comments__c
                , Managers__c
                , Members__c
                , Name__c
                , Type__c
             from Society__c
         order by Members__c desc
        ];
    }

    //
    // Comment list methods
    //
    
    public List<SocietyComment__c> getSocietyPostList() {
        return getSocietyCommentList(new List<String> { 'Post', 'Link' }, 0, 100);
    }
    
    public List<SocietyComment__c> getSocietyCommentList() {
        return getSocietyCommentList(new List<String> { 'Comment', 'Reply' }, 5, 1000);
    }
    
    public List<SocietyComment__c> getSocietyCommentList(List<String> commentType, Integer maxDepth, Integer maxLimit) {
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
             from SocietyComment__c
            where Society__c = :selectedSociety.Id
              and Type__c in :commentType
              and Depth__c < :maxDepth
            limit :maxLimit
        ];
    }

    //
    // Returns the total number of comments under a parent post.
    //

    public Integer getSocietyCommentCount() {
        return [
           select COUNT()
             from SocietyComment__c
            where Society__c = :selectedSociety.Id
              and ParentHierarchy__c = :selectedSocietyPost.Id
              and Type__c in ('Comment', 'Reply')
        ];
    }

    //
    // Update the number of votes
    //
    
    public PageReference insertSocietyVoteLiked() {
        insert new SocietyVote__c(SocietyComment__c = getParam('societyCommentId'), Type__c = 'Liked');
        return null;
    }

    public PageReference insertSocietyVoteDisliked() {
        insert new SocietyVote__c(SocietyComment__c = getParam('societyCommentId'), Type__c = 'Disliked');
        return null;
    }
    
    public PageReference insertSocietyVoteReported() {
        insert new SocietyVote__c(SocietyComment__c = getParam('societyCommentId'), Type__c = 'Reported');
        return null;
    }

    public PageReference insertSocietyVoteSaved() {
        insert new SocietyVote__c(SocietyComment__c = getParam('societyCommentId'), Type__c = 'Saved');
        return null;
    }
    
    public PageReference redirectToPostOrLink() {
        SocietyComment__c societyComment = [
           select Type__c
                , Link__c
                , Society__c
             from SocietyComment__c
            where Id = :getParam('societyCommentId')
              and Type__c in ('Post', 'Link')
        ];
        
        if (societyComment.Type__c == 'Post') {
            PageReference pageReference = System.Page.Society;
            pageReference.getParameters().put('id', societyComment.Society__c);
            pageReference.getParameters().put('postId', societyComment.Id);
            pageReference.setRedirect(true);
            return pageReference;
        } else if (societyComment.Type__c == 'Link') {
            return new PageReference(societyComment.Link__c);
        } else {
            return null; // error?
        }
    }
/*
    public PageReference updateSocietyCommentReplyStarted() {
        commentReply = new SocietyComment__c();
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
             from SocietyComment__c
            where Id = :commentReply.Id
        ];
        return null;
    }

    public PageReference updateReplyCanceled() {
        commentReply = null;
        return null;
    }
*/
}