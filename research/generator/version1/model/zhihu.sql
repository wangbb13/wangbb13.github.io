create table user ( 
  user_id      int primary key, 
  gender      varchar(6), 
  industry      varchar(9), 
  experience      varchar(100) 
); 

create table question ( 
  question_id      int primary key, 
  title      varchar(100), 
  pose_time      timestamp, 
  class      varchar(7) 
); 

create table article ( 
  article_id      int primary key, 
  title      varchar(100), 
  create_time      timestamp, 
  class      varchar(7) 
); 

create table column ( 
  column_id      int primary key, 
  name      varchar(100), 
  create_time      timestamp 
); 

create table thought ( 
  thought_id      int primary key, 
  content      varchar(100), 
  share_time      timestamp 
); 

create table follow ( 
  src_id      varchar(16), 
  tgt_id      varchar(16), 
  primary key (src_id, tgt_id), 
  foreign key (src_id) references user (user_id), 
  foreign key (tgt_id) references user (user_id) 
); 

create table pose ( 
  src_id      varchar(16), 
  tgt_id      varchar(20), 
  primary key (src_id, tgt_id), 
  foreign key (src_id) references user (user_id), 
  foreign key (tgt_id) references question (question_id) 
); 

create table publish ( 
  src_id      varchar(16), 
  tgt_id      varchar(19), 
  primary key (src_id, tgt_id), 
  foreign key (src_id) references user (user_id), 
  foreign key (tgt_id) references article (article_id) 
); 

create table create ( 
  src_id      varchar(16), 
  tgt_id      varchar(18), 
  primary key (src_id, tgt_id), 
  foreign key (src_id) references user (user_id), 
  foreign key (tgt_id) references column (column_id) 
); 

create table share ( 
  src_id      varchar(16), 
  tgt_id      varchar(19), 
  primary key (src_id, tgt_id), 
  foreign key (src_id) references user (user_id), 
  foreign key (tgt_id) references thought (thought_id) 
); 

create table reply ( 
  src_id      varchar(16), 
  tgt_id      varchar(20), 
  primary key (src_id, tgt_id), 
  foreign key (src_id) references user (user_id), 
  foreign key (tgt_id) references question (question_id) 
); 

create table comment ( 
  src_id      varchar(16), 
  tgt_id      varchar(19), 
  primary key (src_id, tgt_id), 
  foreign key (src_id) references user (user_id), 
  foreign key (tgt_id) references thought (thought_id) 
); 

create table contain ( 
  src_id      varchar(18), 
  tgt_id      varchar(19), 
  primary key (src_id, tgt_id), 
  foreign key (src_id) references column (column_id), 
  foreign key (tgt_id) references article (article_id) 
); 

