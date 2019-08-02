create database if not exists order_system2;
use order_system2;

create table dish_table(
  dish_id int not null primary key auto_increment,
  name varchar(50),
  price int
);

insert into dish_table value(null, '红烧肉', 2200);
insert into dish_table value(null, '回锅肉', 2200);
insert into dish_table value(null, '糖醋里脊', 2200);
insert into dish_table value(null, '红烧鱼块', 2200);
insert into dish_table value(null, '东坡肉', 2200);

create table if not exists order_table(
  order_id int primary key auto_increment,
  table_id varchar(50),
  time varchar(50),
  dishes varchar(1024),
  status int
);

insert into order_table(1, '武当派', '2019/08/01', '1,2,3,4');
insert into order_table(2, '少林派', '2019/08/01', '1,3,4');
insert into order_table(3, '华山派', '2019/08/01', '3,4');



