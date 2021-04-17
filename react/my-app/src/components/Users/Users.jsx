import s from './Users.module.css'
let Users = props => {
  if (props.users.length === 0) {
    props.setUsers([
      {
        id: 1,
        photoUrl:
          'https://img5.goodfon.ru/original/320x240/3/ac/kunitsa-zima-sneg-vzgliad.jpg',
        followed: false,
        fullName: 'Dmitry',
        status: 'I am a boss',
        location: { city: 'Minsk', country: 'Belarus' }
      },
      {
        id: 2,
        photoUrl:
          'https://img5.goodfon.ru/original/320x240/3/ac/kunitsa-zima-sneg-vzgliad.jpg',
        followed: true,
        fullName: 'Sasha',
        status: 'I am a boss too',
        location: { city: 'Moscow', country: 'Russia' }
      },
      {
        id: 3,
        photoUrl:
          'https://img5.goodfon.ru/original/320x240/3/ac/kunitsa-zima-sneg-vzgliad.jpg',
        followed: false,
        fullName: 'Andrew',
        status: 'I am a boss too',
        location: { city: 'Kiev', country: 'Ukrain' }
      }
    ])
  }

  return (
    <div>
      {props.users.map(u => (
        <div key={u.id}>
          <span>
            <div>
              <img alt='ava' src={u.photoUrl} className={s.userPhoto} />
            </div>
            {u.followed ? (
              <button onClick={() => props.unfollow(u.id)}>Unfollow</button>
            ) : (
              <button onClick={() => props.follow(u.id)}>Follow</button>
            )}
          </span>
          <span>
            <span>
              <div>{u.fullName}</div>
              <div>{u.status}</div>
            </span>
            <span>
              <div>{u.location.contry}</div>
              <div>{u.location.city}</div>
            </span>
          </span>
        </div>
      ))}
    </div>
  )
}
export default Users
