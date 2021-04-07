import React from "react";
import { NavLink } from "react-router-dom";
import s from "./Navbar.module.css";
console.log(s);

const Navbar = () => {
  return (
    <nav className={s.nav}>
      <div className={s.item}>
        <NavLink to='/profile' activeClassName={s.activeLink}>
          Profile
        </NavLink>
      </div>
      <div className={s.item}>
        <NavLink to='/dialogs' activeClassName={s.activeLink}>
          Dialogs
        </NavLink>
      </div>
    </nav>
  );
};

export default Navbar;
