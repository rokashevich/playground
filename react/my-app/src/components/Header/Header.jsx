import React from 'react'
import { NavLink } from 'react-router-dom'
import s from './Header.module.css'

const Header = props => {
  return (
    <header className={s.header}>
      🔒
      {props.isAuth ? (
        `${props.login}(${props.userId})`
      ) : (
        <NavLink to={'/login'}>Login</NavLink>
      )}
    </header>
  )
}

export default Header
